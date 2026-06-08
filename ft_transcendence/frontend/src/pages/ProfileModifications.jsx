/**
 * @responsable clfouger
 * PAGE DE MODIFICATION DE PROFIL
 */

import { useState, useEffect } from 'react'
import { useNavigate } from 'react-router-dom'
import { useAuth } from '../context/AuthContext'
import { userService } from '../services/userService'
import AppLayout from '../components/layout/AppLayout'

const FONT = 'Gribouillit2.0, sans-serif'

const sectionStyle = {
  backgroundColor: 'white', border: '3px solid black',
  borderRadius: '4px', padding: '1.5rem', marginBottom: '1.25rem'
}

const btnStyle = (bg = 'black', color = '#00FEE5') => ({
  padding: '0.65rem 1.5rem', backgroundColor: bg, color,
  border: '2px solid black', borderRadius: '4px',
  cursor: 'pointer', fontFamily: FONT, fontWeight: 'bold', fontSize: '1rem'
})

export default function ProfileModifications() {
  const navigate = useNavigate()
  const { user, logout } = useAuth()
  const [profile, setProfile] = useState(null)
  const [loading, setLoading] = useState(true)
  const [saving, setSaving] = useState(false)
  const [error, setError] = useState(null)
  const [success, setSuccess] = useState(null)

  const [editingBio, setEditingBio] = useState(false)
  const [newBio, setNewBio] = useState('')
  const [showDeleteConfirm, setShowDeleteConfirm] = useState(false)
  const [deletingAccount, setDeletingAccount] = useState(false)

  useEffect(() => { loadProfile() }, [])

  const loadProfile = async () => {
    try {
      setLoading(true)
      const res = await userService.getCurrentProfile()
      setProfile(res.data)
      setNewBio(res.data.bio || '')
    } catch (err) {
      setError('Erreur lors du chargement du profil')
    } finally {
      setLoading(false)
    }
  }

  const handleUpdateBio = async () => {
    try {
      setSaving(true); setError(null)
      await userService.updateProfile({ bio: newBio })
      await loadProfile()
      setEditingBio(false)
      setSuccess('Biographie mise a jour !')
      setTimeout(() => setSuccess(null), 3000)
    } catch (err) {
      setError('Erreur lors de la mise a jour')
    } finally {
      setSaving(false)
    }
  }

  const handleDeleteAccount = async () => {
    try {
      setDeletingAccount(true)
      await userService.deleteAccount()
      logout()
      navigate('/register')
    } catch (err) {
      setError('Erreur lors de la suppression')
      setDeletingAccount(false)
    }
  }

  if (loading && !profile) {
    return (
      <AppLayout activeNav="settings">
        <div style={{ padding: '2rem', textAlign: 'center', fontFamily: FONT }}>Chargement...</div>
      </AppLayout>
    )
  }

  return (
    <AppLayout activeNav="settings">
      <div style={{ padding: '1.5rem', fontFamily: FONT, maxWidth: '700px' }}>

        {/* TITRE */}
        <div style={{ ...sectionStyle, backgroundColor: 'white', display: 'flex', alignItems: 'center', gap: '1rem' }}>
          <button onClick={() => navigate(`/profile/${user?.id}`)} style={btnStyle('white', '#000')}>← Retour</button>
          <h1 style={{ margin: 0, fontSize: '1.8rem', color: '#000' }}>Modifier mon profil</h1>
        </div>

        {/* MESSAGES */}
        {error && (
          <div style={{ ...sectionStyle, backgroundColor: '#ffe0e0', borderColor: '#c00' }}>
            <p style={{ color: '#c00', margin: 0 }}>⚠️ {error}</p>
          </div>
        )}
        {success && (
          <div style={{ ...sectionStyle, backgroundColor: '#e6ffcc' }}>
            <p style={{ color: '#2a6a00', margin: 0 }}>✓ {success}</p>
          </div>
        )}

        {/* BIOGRAPHIE */}
        <div style={sectionStyle}>
          <h2 style={{ fontSize: '1.2rem', marginBottom: '1rem', color: '#000' }}>Biographie</h2>
          {!editingBio ? (
            <div>
              <p style={{ color: profile?.bio ? '#333' : '#888', marginBottom: '1rem', minHeight: '2rem' }}>
                {profile?.bio || 'Aucune biographie pour l\'instant.'}
              </p>
              <button onClick={() => setEditingBio(true)} style={btnStyle('white', '#000')}>
                ✏️ Modifier
              </button>
            </div>
          ) : (
            <div>
              <textarea
                value={newBio}
                onChange={e => setNewBio(e.target.value)}
                placeholder="Parle de toi..."
                maxLength={500}
                disabled={saving}
                style={{
                  width: '100%', minHeight: '100px', padding: '0.75rem',
                  fontFamily: FONT, fontSize: '1rem', border: '2px solid black',
                  borderRadius: '4px', resize: 'vertical', boxSizing: 'border-box'
                }}
              />
              <p style={{ fontSize: '0.8rem', color: '#888', textAlign: 'right' }}>{newBio.length}/500</p>
              <div style={{ display: 'flex', gap: '0.75rem', marginTop: '0.5rem' }}>
                <button onClick={handleUpdateBio} disabled={saving} style={btnStyle('black', 'white')}>
                  {saving ? 'Sauvegarde...' : '✓ Enregistrer'}
                </button>
                <button onClick={() => { setEditingBio(false); setNewBio(profile?.bio || '') }}
                  style={btnStyle('white', '#000')}>
                  Annuler
                </button>
              </div>
            </div>
          )}
        </div>

        {/* INFOS */}
        <div style={sectionStyle}>
          <h2 style={{ fontSize: '1.2rem', marginBottom: '1rem', color: '#000' }}>Informations</h2>
          <div style={{ display: 'flex', flexDirection: 'column', gap: '0.5rem' }}>
            <p style={{ color: '#333' }}><strong>Pseudo :</strong> {profile?.username || user?.username}</p>
            <p style={{ color: '#333' }}><strong>Email :</strong> {profile?.email || user?.email}</p>
            <p style={{ color: '#333' }}><strong>Membre depuis :</strong> {
              profile?.createdAt
                ? new Date(profile.createdAt).toLocaleDateString('fr-FR', { year: 'numeric', month: 'long', day: 'numeric' })
                : '—'
            }</p>
          </div>
        </div>

        {/* ZONE DANGER */}
        <div style={{ ...sectionStyle, borderColor: '#c00', backgroundColor: '#fff5f5' }}>
          <h2 style={{ fontSize: '1.2rem', marginBottom: '0.5rem', color: '#c00' }}>Zone de danger</h2>
          <p style={{ color: '#666', marginBottom: '1rem', fontSize: '0.9rem' }}>
            La suppression de ton compte est irreversible.
          </p>
          {!showDeleteConfirm ? (
            <button onClick={() => setShowDeleteConfirm(true)} style={btnStyle('#c00')}>
              Supprimer mon compte
            </button>
          ) : (
            <div style={{
              backgroundColor: '#ffe0e0', border: '2px solid #c00',
              borderRadius: '4px', padding: '1rem'
            }}>
              <p style={{ fontWeight: 'bold', marginBottom: '0.75rem', color: '#c00' }}>
                ⚠️ Confirmer la suppression definitive ?
              </p>
              <div style={{ display: 'flex', gap: '0.75rem' }}>
                <button onClick={handleDeleteAccount} disabled={deletingAccount} style={btnStyle('#c00')}>
                  {deletingAccount ? 'Suppression...' : 'Oui, supprimer'}
                </button>
                <button onClick={() => setShowDeleteConfirm(false)} style={btnStyle('white', '#000')}>
                  Non, annuler
                </button>
              </div>
            </div>
          )}
        </div>

      </div>
    </AppLayout>
  )
}
