/**
 * @responsable clfouger
 * PAGE AMIS - Gere la liste des amis
 */

import { useState, useEffect } from 'react'
import { useNavigate } from 'react-router-dom'
import AppLayout from '../components/layout/AppLayout'
import { friendService } from '../services/friendService'
import { useAuth } from '../context/AuthContext'
import { useSocket } from '../context/SocketContext'

const FONT = 'Gribouillit2.0, sans-serif'

const cardStyle = {
  display: 'flex', alignItems: 'center', justifyContent: 'space-between',
  padding: '1rem 1.25rem', backgroundColor: 'white',
  border: '3px solid black', borderRadius: '4px', marginBottom: '0.75rem'
}

const avatarStyle = {
  width: '48px', height: '48px', borderRadius: '50%',
  border: '2px solid black', backgroundColor: '#f0f0f0',
  display: 'flex', alignItems: 'center', justifyContent: 'center',
  fontSize: '1.4rem', flexShrink: 0, overflow: 'hidden'
}

const btnStyle = (color = 'black', text = 'white') => ({
  padding: '0.4rem 1rem', backgroundColor: color, color: text,
  border: '2px solid black', borderRadius: '4px', cursor: 'pointer',
  fontFamily: FONT, fontWeight: 'bold', fontSize: '0.9rem'
})

export const FriendsPage = () => {
  const navigate = useNavigate()
  const { user } = useAuth()
  const { isUserOnline } = useSocket()
  const [friends, setFriends] = useState([])
  const [friendRequests, setFriendRequests] = useState([])
  const [loading, setLoading] = useState(true)
  const [activeTab, setActiveTab] = useState('friends')
  const [searchQuery, setSearchQuery] = useState('')
  const [searchResults, setSearchResults] = useState([])
  const [searching, setSearching] = useState(false)

  // Extrait la personne "autre" d'une relation ami (backend retourne sender+receiver)
  const getFriendUser = (relation) => {
    if (relation.sender && relation.receiver) {
      return relation.senderId === user?.id ? relation.receiver : relation.sender
    }
    // Fallback si deja mappe
    return relation
  }

  useEffect(() => {
    const load = async () => {
      try {
        setLoading(true)
        const [friendsRes, pendingRes] = await Promise.allSettled([
          friendService.getAll(),
          friendService.getPending()
        ])
        if (friendsRes.status === 'fulfilled') setFriends(friendsRes.value.data || [])
        if (pendingRes.status === 'fulfilled') setFriendRequests(pendingRes.value.data || [])
      } catch (err) {
        console.error('Erreur amis:', err)
      } finally {
        setLoading(false)
      }
    }
    load()
  }, [])

  const handleRemoveFriend = async (friendId) => {
    try {
      await friendService.remove(friendId)
      setFriends(prev => prev.filter(f => f.id !== friendId))
    } catch (err) { console.error(err) }
  }

  const handleAcceptRequest = async (requestId) => {
    try {
      await friendService.accept(requestId)
      setFriendRequests(prev => prev.filter(r => r.id !== requestId))
    } catch (err) { console.error(err) }
  }

  const handleSearch = async () => {
    if (!searchQuery.trim()) return
    setSearching(true)
    try {
      const res = await import('../services/api').then(m => m.default.get(`/users/search?q=${encodeURIComponent(searchQuery)}`))
      setSearchResults(res.data || [])
    } catch (err) {
      console.error(err)
      setSearchResults([])
    } finally {
      setSearching(false)
    }
  }

  const handleAddFriend = async (userId) => {
    try {
      await friendService.request(userId)
      setSearchResults(prev => prev.filter(u => u.id !== userId))
    } catch (err) { console.error(err) }
  }

  const TabBtn = ({ id, label, count }) => (
    <button
      onClick={() => setActiveTab(id)}
      style={{
        padding: '0.6rem 1.5rem', fontFamily: FONT, fontWeight: 'bold',
        fontSize: '1rem', cursor: 'pointer', border: '3px solid black',
        borderRadius: '4px',
        backgroundColor: activeTab === id ? '#e0e0e0' : 'white',
        color: '#000'
      }}
    >
      {label} {count > 0 ? `(${count})` : ''}
    </button>
  )

  return (
    <AppLayout activeNav="friends">
      <div style={{ padding: '1.5rem', fontFamily: FONT }}>

        {/* TITRE */}
        <div style={{
          backgroundColor: 'white', border: '3px solid black',
          padding: '1rem 1.5rem', marginBottom: '1.5rem', borderRadius: '4px',
          display: 'flex', alignItems: 'center', gap: '1rem'
        }}>
          <button onClick={() => navigate('/home')} style={btnStyle('white', '#000')}>← Retour</button>
          <h1 style={{ margin: 0, fontSize: '1.8rem', color: '#000' }}>Mes amis</h1>
        </div>

        {/* RECHERCHE */}
        <div style={{
          backgroundColor: 'white', border: '3px solid black',
          padding: '1rem 1.5rem', marginBottom: '1.5rem', borderRadius: '4px'
        }}>
          <p style={{ fontWeight: 'bold', marginBottom: '0.5rem', fontSize: '1rem' }}>Ajouter un ami</p>
          <div style={{ display: 'flex', gap: '0.75rem' }}>
            <input
              type="text"
              value={searchQuery}
              onChange={e => setSearchQuery(e.target.value)}
              onKeyDown={e => e.key === 'Enter' && handleSearch()}
              placeholder="Chercher un pseudo..."
              style={{
                flex: 1, padding: '0.6rem 1rem', fontFamily: FONT,
                border: '2px solid black', borderRadius: '4px', fontSize: '1rem',
                color: 'black', backgroundColor: 'white'
              }}
            />
            <button onClick={handleSearch} disabled={searching} style={btnStyle('black', 'white')}>
              {searching ? '...' : 'Chercher'}
            </button>
          </div>

          {searchResults.length > 0 && (
            <div style={{ marginTop: '0.75rem', display: 'flex', flexDirection: 'column', gap: '0.5rem' }}>
              {searchResults.map(u => (
                <div key={u.id} style={{ ...cardStyle, marginBottom: 0 }}>
                  <div style={{ display: 'flex', alignItems: 'center', gap: '0.75rem' }}>
                    <div style={avatarStyle}>
                      {u.avatar ? <img src={u.avatar} alt="" style={{ width: '100%', height: '100%', objectFit: 'cover' }} /> : '👤'}
                    </div>
                    <span style={{ fontWeight: 'bold' }}>{u.username}</span>
                  </div>
                  <button onClick={() => handleAddFriend(u.id)} style={btnStyle('black', 'white')}>
                    + Ajouter
                  </button>
                </div>
              ))}
            </div>
          )}
        </div>

        {/* ONGLETS */}
        <div style={{ display: 'flex', gap: '0.75rem', marginBottom: '1rem' }}>
          <TabBtn id="friends" label="👥 Amis" count={friends.length} />
          <TabBtn id="requests" label="📬 Demandes" count={friendRequests.length} />
        </div>

        {/* CONTENU */}
        {loading ? (
          <p style={{ textAlign: 'center', padding: '2rem', fontFamily: FONT }}>Chargement...</p>
        ) : activeTab === 'friends' ? (
          friends.length === 0 ? (
            <div style={{
              backgroundColor: 'white', border: '3px solid black', borderRadius: '4px',
              padding: '3rem', textAlign: 'center'
            }}>
              <p style={{ fontSize: '1.2rem', color: '#555' }}>Aucun ami pour l'instant 👥</p>
              <p style={{ fontSize: '0.95rem', color: '#888', marginTop: '0.5rem' }}>
                Utilise la recherche ci-dessus pour en ajouter !
              </p>
            </div>
          ) : (
            friends.map(relation => {
              const friend = getFriendUser(relation)
              const online = isUserOnline(friend.id)
              return (
              <div key={relation.id} style={cardStyle}>
                <div style={{ display: 'flex', alignItems: 'center', gap: '0.75rem' }}>
                  <div style={avatarStyle}>
                    {friend.avatar
                      ? <img src={friend.avatar} alt="" style={{ width: '100%', height: '100%', objectFit: 'cover' }} />
                      : '👤'}
                  </div>
                  <div>
                    <p style={{ fontWeight: 'bold', fontSize: '1rem' }}>{friend.username || 'Utilisateur'}</p>
                    <p style={{
                      fontSize: '0.85rem',
                      fontFamily: FONT,
                      color: online ? '#2a9d2a' : '#999',
                      fontWeight: 'bold'
                    }}>
                      {online ? 'en ligne' : 'hors ligne'}
                    </p>
                  </div>
                </div>
                <div style={{ display: 'flex', gap: '0.5rem' }}>
                  <button onClick={() => navigate(`/profile/${friend.id}`)} style={btnStyle('white', '#000')}>Profil</button>
                  <button onClick={() => navigate(`/messages?userId=${friend.id}&username=${encodeURIComponent(friend.username || 'Utilisateur')}`)} style={btnStyle('black', 'white')}>Message</button>
                  <button onClick={() => handleRemoveFriend(relation.id)} style={btnStyle('white', '#c00')}>Retirer</button>
                </div>
              </div>
              )
            })
          )
        ) : (
          friendRequests.length === 0 ? (
            <div style={{
              backgroundColor: 'white', border: '3px solid black', borderRadius: '4px',
              padding: '3rem', textAlign: 'center'
            }}>
              <p style={{ fontSize: '1.2rem', color: '#555' }}>Aucune demande en attente 📭</p>
            </div>
          ) : (
            friendRequests.map(req => (
              <div key={req.id} style={cardStyle}>
                <div style={{ display: 'flex', alignItems: 'center', gap: '0.75rem' }}>
                  <div style={avatarStyle}>
                    {req.sender?.avatar
                      ? <img src={req.sender.avatar} alt="" style={{ width: '100%', height: '100%', objectFit: 'cover' }} />
                      : '👤'}
                  </div>
                  <span style={{ fontWeight: 'bold' }}>{req.sender?.username || req.username || 'Utilisateur'}</span>
                </div>
                <div style={{ display: 'flex', gap: '0.5rem' }}>
                  <button onClick={() => handleAcceptRequest(req.id)} style={btnStyle('black', 'white')}>✓ Accepter</button>
                  <button onClick={() => setFriendRequests(prev => prev.filter(r => r.id !== req.id))} style={btnStyle('white', '#c00')}>✕ Refuser</button>
                </div>
              </div>
            ))
          )
        )}
      </div>
    </AppLayout>
  )
}
