/**
 * @responsable clfouger
 * PAGE PROFIL - Affiche le profil de l'utilisateur connecte
 */

import { useState, useEffect } from 'react'
import { useNavigate, useParams } from 'react-router-dom'
import AppLayout from '../components/layout/AppLayout'
import { useAuth } from '../context/AuthContext'
import { userService } from '../services/userService'
import { postService } from '../services/postService'
import { friendService } from '../services/friendService'

import img1 from '../assets/images/img1.png'
import img2 from '../assets/images/img2.png'
import img3 from '../assets/images/img3.png'
import img4 from '../assets/images/img4.png'
import img5 from '../assets/images/img5.png'
const avatars = [img1, img2, img3, img4, img5]

const FONT = 'Gribouillit2.0, sans-serif'

export const ProfilePage = () => {
  const { user, logout } = useAuth()
  const navigate = useNavigate()
  const { userId } = useParams()
  const [profile, setProfile] = useState(null)
  const [posts, setPosts] = useState([])
  const [loading, setLoading] = useState(true)

  const targetId = userId || user?.id

  useEffect(() => {
    const load = async () => {
      if (!targetId) return
      try {
        setLoading(true)
        const [profileRes, postsRes] = await Promise.allSettled([
          userService.getProfile(targetId),
          postService.getByUser(targetId)
        ])
        if (profileRes.status === 'fulfilled') setProfile(profileRes.value.data)
        if (postsRes.status === 'fulfilled') setPosts(postsRes.value.data || [])
      } catch (err) {
        console.error('Erreur profil:', err)
      } finally {
        setLoading(false)
      }
    }
    load()
  }, [targetId])

  const isOwn = !userId || userId === String(user?.id)

  const handleLogout = () => { logout(); navigate('/login') }
  const handleAddFriend = async () => {
    try { await friendService.request(Number(userId)) } catch (err) { console.error(err) }
  }
  const handleMessage = () => { navigate('/messages') }

  const displayName = profile?.username || user?.username || 'Utilisateur'

  // Pour le profil de l'utilisateur connecte : lire depuis localStorage (meme logique que la sidebar)
  let avatarSrc = profile?.avatar || null
  if (isOwn && !avatarSrc) {
    const idx = localStorage.getItem('selectedAvatar')
    if (idx !== null) avatarSrc = avatars[parseInt(idx)]
  }

  return (
    <AppLayout activeNav="profile">
      <div style={{ padding: '1.5rem', fontFamily: FONT }}>

        {/* HEADER CARTE PROFIL */}
        <div style={{
          backgroundColor: 'white', border: '3px solid black',
          borderRadius: '4px', overflow: 'hidden', marginBottom: '1.5rem'
        }}>
          {/* Bandeau couleur */}
          <div style={{ height: '80px', backgroundColor: '#f5f5f5', borderBottom: '2px solid black' }} />

          {/* Info profil */}
          <div style={{ padding: '0 1.5rem 1.5rem', position: 'relative' }}>
            {/* Avatar */}
            <div style={{
              width: '90px', height: '90px', borderRadius: '50%',
              border: '4px solid black', backgroundColor: '#f0f0f0',
              position: 'absolute', top: '-45px', left: '1.5rem',
              overflow: 'hidden', display: 'flex', alignItems: 'center', justifyContent: 'center',
              fontSize: '2.5rem', backgroundColor: '#f0f0f0'
            }}>
              {avatarSrc
                ? <img src={avatarSrc} alt={displayName} style={{ width: '100%', height: '100%', objectFit: 'cover' }} />
                : '👤'}
            </div>

            {/* Boutons action */}
            <div style={{ display: 'flex', justifyContent: 'flex-end', gap: '0.75rem', paddingTop: '0.75rem', marginBottom: '2rem' }}>
              {isOwn ? (
                <>
                  <button
                    onClick={() => navigate('/profile-modifications')}
                    style={{
                      padding: '0.5rem 1.25rem', backgroundColor: 'white',
                      border: '2px solid black', borderRadius: '4px',
                      cursor: 'pointer', fontFamily: FONT, fontWeight: 'bold'
                    }}
                  >
                    ✏️ Modifier
                  </button>
                  <button
                    onClick={handleLogout}
                    style={{
                      padding: '0.5rem 1.25rem', backgroundColor: 'black',
                      border: '2px solid black', borderRadius: '4px', color: '#00FEE5',
                      cursor: 'pointer', fontFamily: FONT, fontWeight: 'bold'
                    }}
                  >
                    Deconnexion
                  </button>
                </>
              ) : (
                <>
                  <button
                    onClick={handleAddFriend}
                    style={{
                      padding: '0.5rem 1.25rem', backgroundColor: 'black',
                      border: '2px solid black', borderRadius: '4px', color: 'white',
                      cursor: 'pointer', fontFamily: FONT, fontWeight: 'bold'
                    }}
                  >
                    + Ajouter
                  </button>
                  <button
                    onClick={handleMessage}
                    style={{
                      padding: '0.5rem 1.25rem', backgroundColor: 'white',
                      border: '2px solid black', borderRadius: '4px', color: 'black',
                      cursor: 'pointer', fontFamily: FONT, fontWeight: 'bold'
                    }}
                  >
                    ✉️ Message
                  </button>
                </>
              )}
            </div>

            <h2 style={{ fontSize: '1.6rem', fontWeight: 'bold', color: '#000', margin: '0 0 0.25rem' }}>
              {displayName}
            </h2>
            <p style={{ color: '#555', fontSize: '0.9rem', marginBottom: '0.75rem' }}>
              {profile?.email || user?.email || ''}
            </p>
            {profile?.bio && (
              <p style={{ color: '#333', fontSize: '1rem', marginBottom: '0.75rem' }}>{profile.bio}</p>
            )}

            {/* STATS */}
            <div style={{ display: 'flex', gap: '1.5rem' }}>
              {[
                { label: 'publications', value: posts.length },
                { label: 'amis', value: profile?.friendCount ?? 0 },
              ].map(({ label, value }) => (
                <div key={label} style={{ display: 'flex', gap: '0.35rem', alignItems: 'baseline' }}>
                  <span style={{ fontWeight: 'bold', fontSize: '1.1rem' }}>{value}</span>
                  <span style={{ fontSize: '0.9rem', color: '#555' }}>{label}</span>
                </div>
              ))}
            </div>
          </div>
        </div>

        {/* TITRE PUBLICATIONS */}
        <div style={{
          backgroundColor: 'white', border: '3px solid black',
          padding: '0.75rem 1.25rem', borderRadius: '4px', marginBottom: '1rem'
        }}>
          <h3 style={{ margin: 0, fontSize: '1.1rem', fontFamily: FONT }}>
            Publications ({posts.length})
          </h3>
        </div>

        {/* GRILLE POSTS */}
        {loading ? (
          <p style={{ textAlign: 'center', padding: '2rem', fontFamily: FONT }}>Chargement...</p>
        ) : posts.length === 0 ? (
          <div style={{
            backgroundColor: 'white', border: '3px solid black',
            borderRadius: '4px', padding: '3rem', textAlign: 'center'
          }}>
            <p style={{ color: '#555', fontSize: '1.1rem', fontFamily: FONT }}>Aucune publication pour l'instant 🎨</p>
            {isOwn && (
              <button
                onClick={() => navigate('/draw')}
                style={{
                  marginTop: '1rem', padding: '0.75rem 1.5rem',
                  backgroundColor: 'black', color: '#00FEE5',
                  border: '2px solid black', borderRadius: '4px',
                  cursor: 'pointer', fontFamily: FONT, fontWeight: 'bold', fontSize: '1rem'
                }}
              >
                🎨 Creer une publication
              </button>
            )}
          </div>
        ) : (
          <div style={{
            display: 'grid', gridTemplateColumns: 'repeat(auto-fill, minmax(200px, 1fr))',
            gap: '0.75rem'
          }}>
            {posts.map(post => (
              <div key={post.id} style={{
                border: '3px solid black', borderRadius: '4px',
                overflow: 'hidden', backgroundColor: 'white', cursor: 'pointer'
              }}>
                {post.imageUrl && (
                  <img src={post.imageUrl} alt={post.caption || 'dessin'}
                    style={{ width: '100%', aspectRatio: '1', objectFit: 'cover', display: 'block' }} />
                )}
                {post.caption && (
                  <p style={{
                    padding: '0.5rem 0.75rem', fontSize: '0.85rem',
                    fontFamily: FONT, borderTop: '2px solid black', margin: 0
                  }}>
                    {post.caption}
                  </p>
                )}
              </div>
            ))}
          </div>
        )}
      </div>
    </AppLayout>
  )
}
