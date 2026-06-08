/**
 * @responsable clfouger
 * PAGE ACCUEIL - Feed de dessins (style Miiverse)
 */

import { useState, useEffect, useCallback, useRef } from 'react'
import { useNavigate } from 'react-router-dom'
import { formatDistanceToNow } from 'date-fns'
import { fr } from 'date-fns/locale'
import { io } from 'socket.io-client'
import { commentService } from '../services/commentService'
import { postService } from '../services/postService'
import { useAuth } from '../context/AuthContext'
import { useNotification } from '../context/NotificationContext'
import '../styles/homepage.css'

// Assets - Images
import img1 from '../assets/images/img1.png'
import img2 from '../assets/images/img2.png'
import img3 from '../assets/images/img3.png'
import img4 from '../assets/images/img4.png'
import img5 from '../assets/images/img5.png'

// Assets - Icons
import brushIcon from '../assets/logo/canva tools/brush.png'
import notificationsIcon from '../assets/logo/onglets/notif.png'
import notificationsIconNotif from '../assets/logo/onglets/notif_1.png'
import messagesIcon from '../assets/logo/onglets/private_messages.png'
import messagesIconNotif from '../assets/logo/onglets/private_messages_notif.png'
import friendsIcon from '../assets/logo/onglets/friends.png'
import settingsIcon from '../assets/logo/onglets/settings.png'
import chatIcon from '../assets/logo/onglets/chat.png'

// Assets - Logos
import logoGribouillit from '../assets/logo/page_title/logo_gribouillit.png'
import logoFilDactu from '../assets/logo/page_title/logo_fil_dactu.png'

// Assets - Interactions (Like, Repost, Commentaires)
import likeIcon from '../assets/logo/publications interactions/like.png'
import likeDoneIcon from '../assets/logo/publications interactions/like_done.png'
import repostIcon from '../assets/logo/publications interactions/repost.png'
import repostDoneIcon from '../assets/logo/publications interactions/repost_done.png'
import commentIcon from '../assets/logo/publications interactions/commentaires.png'

// Assets - Background
import bg from '../assets/background/background.png'

export const HomePage = () => {
  const [posts, setPosts] = useState([])
  const [loading, setLoading] = useState(true)
  const [error, setError] = useState(null)
  const [userAvatar, setUserAvatar] = useState(null)
  const [likedPosts, setLikedPosts] = useState(new Set())
  const [repostedPosts, setRepostedPosts] = useState(new Set())
  const [openComments, setOpenComments] = useState(null)
  const [commentTexts, setCommentTexts] = useState({})
  const [postComments, setPostComments] = useState({})
  // Image agrandie en plein ecran (null = fermee)
  const [expandedImage, setExpandedImage] = useState(null)

  // Chat en direct
  const [chatMessages, setChatMessages] = useState([])
  const [chatInput, setChatInput] = useState('')
  const chatSocketRef = useRef(null)
  const chatBottomRef = useRef(null)
  const { user } = useAuth()
  const { unreadCount } = useNotification()
  const navigate = useNavigate()

  const avatars = [img1, img2, img3, img4, img5]

  useEffect(() => {
    if (user?.avatar) setUserAvatar(user.avatar)
    else {
      const idx = localStorage.getItem('selectedAvatar')
      if (idx !== null) setUserAvatar(avatars[parseInt(idx)])
    }
  }, [user])

  // Charger les posts depuis l'API
  const loadPosts = useCallback(async () => {
    try {
      setLoading(true)
      const response = await postService.getAll(1, 20)
      const fetched = response.data || []
      setPosts(fetched)
      // Initialiser les likes depuis la reponse API
      const alreadyLiked = new Set(
        fetched
          .filter(p => p.likes?.some(l => l.userId === user?.id))
          .map(p => p.id)
      )
      setLikedPosts(alreadyLiked)
      setError(null)
    } catch (err) {
      console.error('Erreur lors du chargement des posts:', err)
      setPosts([])
      setError('Impossible de charger les posts.')
    } finally {
      setLoading(false)
    }
  }, [user?.id])

  useEffect(() => {
    loadPosts()
  }, [loadPosts])

  const formatTime = (dateString) => {
    try {
      return formatDistanceToNow(new Date(dateString), { addSuffix: true, locale: fr })
    } catch {
      return 'a l\'instant'
    }
  }

  const handleLike = async (post) => {
    const isLiked = likedPosts.has(post.id)
    setLikedPosts(prev => {
      const next = new Set(prev)
      isLiked ? next.delete(post.id) : next.add(post.id)
      return next
    })
    // Optimistic update sur le compteur local
    setPosts(prev => prev.map(p =>
      p.id === post.id
        ? { ...p, _count: { ...p._count, likes: (p._count?.likes || 0) + (isLiked ? -1 : 1) } }
        : p
    ))
    try {
      if (isLiked) {
        await postService.unlike(post.id)
      } else {
        await postService.like(post.id)
      }
    } catch {
      // Rollback si l'API echoue (post fictif par exemple)
    }
  }

  const handleRepost = async (post) => {
    const isReposted = repostedPosts.has(post.id)
    setRepostedPosts(prev => {
      const next = new Set(prev)
      isReposted ? next.delete(post.id) : next.add(post.id)
      return next
    })
    // Optimistic update sur le compteur local
    setPosts(prev => prev.map(p =>
      p.id === post.id
        ? { ...p, _count: { ...p._count, reposts: (p._count?.reposts || 0) + (isReposted ? -1 : 1) } }
        : p
    ))
    try {
      if (isReposted) {
        await postService.unrepost(post.id)
      } else {
        await postService.repost(post.id)
      }
    } catch {
      // Rollback si l'API echoue
    }
  }

  const toggleComments = async (post) => {
    if (openComments === post.id) {
      setOpenComments(null)
      return
    }
    setOpenComments(post.id)
    if (!postComments[post.id]) {
      try {
        const res = await commentService.getByPost(post.id)
        setPostComments(prev => ({ ...prev, [post.id]: res.data || [] }))
      } catch {
        setPostComments(prev => ({ ...prev, [post.id]: [] }))
      }
    }
  }

  const handleComment = async (post) => {
    const text = (commentTexts[post.id] || '').trim()
    if (!text) return
    const fake = { id: Date.now(), content: text, user: { username: user?.username || 'moi' } }
    setPostComments(prev => ({ ...prev, [post.id]: [...(prev[post.id] || []), fake] }))
    setCommentTexts(prev => ({ ...prev, [post.id]: '' }))
    setPosts(prev => prev.map(p =>
      p.id === post.id
        ? { ...p, _count: { ...p._count, comments: (p._count?.comments || 0) + 1 } }
        : p
    ))
    try {
      await commentService.create(post.id, text)
    } catch {
      // post fictif, on garde l'optimistic update
    }
  }

  // Socket chat global
  useEffect(() => {
    const token = localStorage.getItem('token')
    if (!token) return
    const socket = io(`${import.meta.env.VITE_WS_URL || window.location.origin}/chat`, {
      auth: { token },
      reconnection: true,
    })
    chatSocketRef.current = socket
    socket.on('connect', () => {
      socket.emit('authenticate', { userId: user?.id })
      socket.emit('joinRoom', { roomId: 'global' })
    })
    // Historique des 50 derniers messages recu au moment de rejoindre le chat
    socket.on('chatHistory', (history) => {
      setChatMessages(history.map(msg => ({
        id: msg.id,
        username: msg.username,
        text: msg.content,
        ts: new Date(msg.createdAt),
        own: msg.senderId === user?.id,
      })))
    })
    socket.on('newMessage', (msg) => {
      // Ignorer les messages envoyes par nous-memes (deja ajoutes en optimiste)
      if (msg.senderId && user?.id && msg.senderId === user.id) return
      if (msg.senderUsername && user?.username && msg.senderUsername === user.username) return
      setChatMessages(prev => [...prev, {
        id: msg.id || Date.now(),
        username: msg.senderUsername || msg.senderId || '?',
        text: msg.content,
        ts: new Date(msg.timestamp),
      }])
    })
    return () => { socket.disconnect() }
  }, [user?.id])

  // Scroll automatique chat
  useEffect(() => {
    chatBottomRef.current?.scrollIntoView({ behavior: 'smooth' })
  }, [chatMessages])

  const sendChat = () => {
    const text = chatInput.trim()
    if (!text) return
    // Affichage immediat
    setChatMessages(prev => [...prev, {
      id: Date.now(),
      username: user?.username || 'moi',
      text,
      ts: new Date(),
      own: true,
    }])
    setChatInput('')
    // Envoi socket
    chatSocketRef.current?.emit('sendMessage', {
      roomId: 'global',
      content: text,
      senderId: user?.id,
      senderUsername: user?.username,
    })
  }

  return (
    <div className="homepage">
      {/* SIDEBAR GAUCHE */}      <aside className="homepage-sidebar">
        {/* Logo du site */}
        <img
          src={logoGribouillit}
          alt="Gribouillit"
          style={{
            width: 'auto',
            height: '100px',
            display: 'block',
            margin: '0 auto'
          }}
        />

        {/* Navigation */}
        <nav className="sidebar-nav">
          <button 
            className="nav-btn"
            onClick={() => navigate(`/profile/${user?.id}`)}
          >
            {userAvatar ? (
              <img 
                src={userAvatar} 
                alt="Votre avatar" 
                style={{
                  width: '56px',
                  height: '56px',
                  borderRadius: '50%',
                  border: '2px solid black',
                  objectFit: 'cover',
                  flexShrink: 0
                }}
              />
            ) : (
              <div style={{
                width: '56px',
                height: '56px',
                borderRadius: '50%',
                border: '2px solid black',
                display: 'flex',
                alignItems: 'center',
                justifyContent: 'center',
                backgroundColor: '#f0f0f0',
                flexShrink: 0,
                fontSize: '1.5rem'
              }}>
                👤
              </div>
            )}
            <div style={{ display: 'flex', flexDirection: 'column', textAlign: 'left' }}>
              <span>mon profil</span>
              {user?.username && (
                <span style={{ fontSize: '0.8rem', color: '#666', fontWeight: 400 }}>
                  @{user.username}
                </span>
              )}
            </div>
          </button>

          <button 
            className="nav-btn"
            onClick={() => navigate('/notifications')}
          >
            <div style={{ position: 'relative', display: 'flex', alignItems: 'center' }}>
              <img src={unreadCount > 0 ? notificationsIconNotif : notificationsIcon} alt="Notifications" className="nav-icon" />
              {unreadCount > 0 && (
                <span style={{
                  position: 'absolute', top: '-6px', right: '-8px',
                  backgroundColor: '#FF4444', color: 'white',
                  borderRadius: '50%', width: '18px', height: '18px',
                  fontSize: '0.7rem', fontWeight: 'bold',
                  display: 'flex', alignItems: 'center', justifyContent: 'center',
                  border: '2px solid black',
                }}>
                  {unreadCount > 9 ? '9+' : unreadCount}
                </span>
              )}
            </div>
            <span>notifications</span>
          </button>

          <button 
            className="nav-btn"
            onClick={() => navigate('/messages')}
          >
            <div style={{ position: 'relative', display: 'flex', alignItems: 'center' }}>
              <img src={unreadCount > 0 ? messagesIconNotif : messagesIcon} alt="Messages" className="nav-icon" />
            </div>
            <span>mes messages</span>
          </button>

          <button 
            className="nav-btn"
            onClick={() => navigate('/friends')}
          >
            <img src={friendsIcon} alt="Amis" className="nav-icon" />
            <span>mes amis</span>
          </button>

          <button 
            className="nav-btn"
            onClick={() => navigate('/profile-modifications')}
          >
            <img src={settingsIcon} alt="Parametres" className="nav-icon" />
            <span>parametres</span>
          </button>
        </nav>

        {/* Bouton Gribouiller */}
        <button
          className="btn-tweet"
          onClick={() => navigate('/draw')}
        >
          <img src={brushIcon} alt="Pinceau" className="tweet-icon" />
          <span>gribouiller !</span>
        </button>
      </aside>

      {/* CONTENU PRINCIPAL */}
      <main className="homepage-main">
        <img 
          src={logoFilDactu} 
          alt="Fil d'actualite" 
          style={{
            width: 'auto',
            height: '80px',
            display: 'block',
            marginBottom: '1rem'
          }}
        />

        {/* FEED */}
        <div className="feed-container">
          {loading && (
            <div className="loading-state">
              <div className="loading-icon">⏳</div>
              <p>Chargement des dessins...</p>
            </div>
          )}

          {!loading && posts.map((post, index) => (
            <div key={post.id} className="post-card">

              {/* DESCRIPTION EN HAUT */}
              <div className="post-description">
                {post.caption || 'Aucune description'}
              </div>

              {/* LIGNE CENTRALE : info gauche + dessin droite */}
              <div className="post-body">
                <div className="post-left">
                  <div
                    className="post-username"
                    onClick={() => navigate(`/profile/${post.user?.id}`)}
                    style={{ cursor: 'pointer' }}
                  >
                    {post.user?.username || 'anonyme'}
                  </div>
                  <div className="post-timestamp">{formatTime(post.createdAt)}</div>
                </div>

                <div className="post-right">
                  {post.imageUrl ? (
                    <img src={post.imageUrl} alt="Dessin" className="post-drawing" />
                  ) : (
                    <div className="post-drawing-empty">🎨</div>
                  )}
                  {/* Bouton pour ouvrir l'image en plein ecran */}
                  {post.imageUrl && (
                    <button
                      className="expand-btn"
                      onClick={() => setExpandedImage(post.imageUrl)}
                    >
                      Agrandir
                    </button>
                  )}
                </div>
              </div>

              {/* ACTIONS EN BAS */}
              <div className="post-actions">
                <button
                  className={`action-btn like-btn${likedPosts.has(post.id) ? ' liked' : ''}`}
                  onClick={() => handleLike(post)}
                  title="J'aime"
                >
                  <img 
                    src={likedPosts.has(post.id) ? likeDoneIcon : likeIcon} 
                    alt="Like" 
                    style={{ width: '24px', height: '24px' }}
                  />
                  <span className="action-count">{post._count?.likes || 0}</span>
                </button>

                <button
                  className={`action-btn repost-btn${repostedPosts.has(post.id) ? ' reposted' : ''}`}
                  onClick={() => handleRepost(post)}
                  title="Republier"
                >
                  <img 
                    src={repostedPosts.has(post.id) ? repostDoneIcon : repostIcon} 
                    alt="Repost" 
                    style={{ width: '24px', height: '24px' }}
                  />
                  <span className="action-count">{post._count?.reposts || 0}</span>
                </button>

                <button
                  className={`action-btn comment-btn${openComments === post.id ? ' open' : ''}`}
                  onClick={() => toggleComments(post)}
                  title="Commentaires"
                >
                  <img 
                    src={commentIcon} 
                    alt="Commentaires" 
                    style={{ width: '24px', height: '24px' }}
                  />
                  <span className="action-count">{post._count?.comments || 0}</span>
                </button>
              </div>

              {/* SECTION COMMENTAIRES */}
              {openComments === post.id && (
                <div className="post-comments">
                  <div className="comment-list">
                    {(postComments[post.id] || []).length === 0 && (
                      <div className="comment-item" style={{ color: '#888', fontStyle: 'italic' }}>
                        Aucun commentaire pour l'instant...
                      </div>
                    )}
                    {(postComments[post.id] || []).map(c => (
                      <div key={c.id} className="comment-item">
                        <strong>@{c.user?.username || c.author?.username || 'anonyme'}</strong>
                        {' '}{c.content || c.text}
                      </div>
                    ))}
                  </div>
                  <div className="comment-input-row">
                    <input
                      className="comment-input"
                      type="text"
                      placeholder="Ecris un commentaire..."
                      value={commentTexts[post.id] || ''}
                      onChange={e => setCommentTexts(prev => ({ ...prev, [post.id]: e.target.value }))}
                      onKeyDown={e => e.key === 'Enter' && handleComment(post)}
                    />
                    <button className="comment-send-btn" onClick={() => handleComment(post)}>
                      Envoyer
                    </button>
                  </div>
                </div>
              )}
            </div>
          ))}
        </div>
      </main>

      {/* PANEL CHAT EN DIRECT */}
      <aside className="chat-panel">
        <div className="chat-panel-header">
          <img src={chatIcon} alt="Chat" style={{ width: '24px', height: '24px', marginRight: '8px' }} />
          chat en direct
        </div>

        <div className="chat-messages">
          {chatMessages.map(msg => (
            <div key={msg.id} className={`chat-msg${msg.own ? ' chat-msg-own' : ''}`}>
              <span className="chat-msg-user">@{msg.username}</span>
              <span className="chat-msg-text">{msg.text}</span>
              <span className="chat-msg-time">
                {formatDistanceToNow(msg.ts, { addSuffix: true, locale: fr })}
              </span>
            </div>
          ))}
          <div ref={chatBottomRef} />
        </div>

        <div className="chat-input-row">
          <input
            className="chat-input"
            type="text"
            placeholder="Dis quelque chose..."
            value={chatInput}
            onChange={e => setChatInput(e.target.value)}
            onKeyDown={e => e.key === 'Enter' && sendChat()}
          />
          <button className="chat-send-btn" onClick={sendChat}>→</button>
        </div>
      </aside>

      {/* Modal plein ecran pour agrandir un dessin */}
      {expandedImage && (
        <div
          onClick={() => setExpandedImage(null)}
          style={{
            position: 'fixed', inset: 0, zIndex: 1000,
            backgroundColor: 'rgba(0,0,0,0.85)',
            display: 'flex', alignItems: 'center', justifyContent: 'center',
            cursor: 'zoom-out',
          }}
        >
          <img
            src={expandedImage}
            alt="Dessin agrandi"
            onClick={e => e.stopPropagation()}
            style={{
              maxWidth: '90vw', maxHeight: '90vh',
              border: '4px solid black', borderRadius: '8px',
              boxShadow: '8px 8px 0 black',
            }}
          />
          <button
            onClick={() => setExpandedImage(null)}
            style={{
              position: 'absolute', top: '20px', right: '24px',
              background: 'white', border: '3px solid black',
              borderRadius: '6px', padding: '0.4rem 1rem',
              fontFamily: 'Gribouillit2.0, sans-serif',
              fontSize: '1.1rem', fontWeight: 'bold',
              cursor: 'pointer', boxShadow: '3px 3px 0 black',
            }}
          >
            Fermer
          </button>
        </div>
      )}
    </div>
  )
}
