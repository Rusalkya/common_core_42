/**
 * @responsable clfouger
 * PAGE MESSAGES - Chat avec les amis
 */

import { useState, useEffect, useRef } from 'react'
import { useNavigate, useSearchParams } from 'react-router-dom'
import { io } from 'socket.io-client'
import AppLayout from '../components/layout/AppLayout'
import { messageService } from '../services/messageService'
import { useAuth } from '../context/AuthContext'

const FONT = 'Gribouillit2.0, sans-serif'

export const MessagesPage = () => {
  const navigate = useNavigate()
  const [searchParams] = useSearchParams()
  const { user } = useAuth()
  const [conversations, setConversations] = useState([])
  const [selectedConv, setSelectedConv] = useState(null)
  const [messages, setMessages] = useState([])
  const [messageText, setMessageText] = useState('')
  const [loading, setLoading] = useState(true)
  const bottomRef = useRef(null)
  const pendingUserIdRef = useRef(null)
  const selectedConvRef = useRef(null)
  const socketRef = useRef(null)

  // Garder selectedConvRef synchronise pour le socket listener
  useEffect(() => { selectedConvRef.current = selectedConv }, [selectedConv])

  // Socket : ecoute des messages prives en temps reel
  useEffect(() => {
    const token = localStorage.getItem('token')
    if (!token || !user?.id) return
    const socket = io(`${import.meta.env.VITE_WS_URL || 'http://localhost:3001'}/chat`, {
      auth: { token },
      reconnection: true,
    })
    socketRef.current = socket
    socket.on('connect', () => {
      socket.emit('authenticate', { userId: user.id })
    })
    socket.on('newPrivateMessage', (msg) => {
      const conv = selectedConvRef.current
      // Ajouter au chat si on est dans la bonne conversation
      if (conv && (msg.senderId === conv.userId || msg.receiverId === conv.userId)) {
        setMessages(prev => {
          // Eviter les doublons (message deja ajoute en optimiste)
          if (prev.some(m => m.id === msg.id)) return prev
          return [...prev, msg]
        })
      }
      // Mettre a jour le dernier message dans la liste des conversations
      setConversations(prev => prev.map(c =>
        c.userId === msg.senderId || c.userId === msg.receiverId
          ? { ...c, lastMessage: msg.content, lastAt: msg.createdAt }
          : c
      ))
    })
    return () => { socket.disconnect() }
  }, [user?.id])

  useEffect(() => {
    const load = async () => {
      try {
        setLoading(true)
        // Lire les params URL avant le chargement
        const urlUserId = searchParams.get('userId')
        const urlUsername = searchParams.get('username')
        if (urlUserId) pendingUserIdRef.current = { id: Number(urlUserId), username: urlUsername || 'Utilisateur' }

        const res = await messageService.getConversations()
        const messages = res.data || res || []
        // Grouper par interlocuteur unique
        const convMap = {}
        messages.forEach(msg => {
          const partner = msg.senderId === user?.id ? msg.receiver : msg.sender
          if (!partner) return
          const pid = partner.id
          if (!convMap[pid] || new Date(msg.createdAt) > new Date(convMap[pid].lastAt)) {
            convMap[pid] = {
              id: pid,
              userId: pid,
              username: partner.username,
              avatar: partner.avatar,
              lastMessage: msg.content,
              lastAt: msg.createdAt
            }
          }
        })
        // Si un userId est dans l'URL mais pas encore en conv, creer un placeholder
        if (urlUserId && !convMap[urlUserId]) {
          convMap[urlUserId] = {
            id: Number(urlUserId),
            userId: Number(urlUserId),
            username: urlUsername || 'Utilisateur',
            avatar: null,
            lastMessage: '',
            lastAt: ''
          }
        }
        const convList = Object.values(convMap)
        setConversations(convList)
        // Auto-selectionner si userId dans l'URL
        if (urlUserId) {
          const target = convList.find(c => c.userId === Number(urlUserId))
          if (target) {
            setSelectedConv(target)
            try {
              const hist = await messageService.getHistory(target.userId)
              setMessages(hist.data || [])
            } catch { setMessages([]) }
          }
        }
      } catch (err) {
        console.error('Erreur conversations:', err)
      } finally {
        setLoading(false)
      }
    }
    load()
  }, [user])

  useEffect(() => {
    bottomRef.current?.scrollIntoView({ behavior: 'smooth' })
  }, [messages])

  const handleSelectConv = async (conv) => {
    setSelectedConv(conv)
    try {
      const res = await messageService.getHistory(conv.userId || conv.id)
      setMessages(res.data || [])
    } catch (err) {
      console.error('Erreur messages:', err)
      setMessages([])
    }
  }

  const handleSend = async () => {
    if (!messageText.trim() || !selectedConv) return
    const text = messageText.trim()
    const fakeId = `pending_${Date.now()}`
    setMessageText('')
    const fake = { id: fakeId, content: text, senderId: user?.id, isOwn: true, createdAt: new Date().toISOString() }
    setMessages(prev => [...prev, fake])
    try {
      const res = await messageService.send(selectedConv.userId || selectedConv.id, text)
      const saved = res.data || res
      // Remplacer le message optimiste par le vrai (avec le vrai id)
      if (saved?.id) {
        setMessages(prev => prev.map(m => m.id === fakeId ? { ...saved, isOwn: true } : m))
      }
    } catch (err) {
      console.error('Erreur envoi:', err)
      setMessages(prev => prev.filter(m => m.id !== fakeId))
    }
  }

  const mainContent = (
    <div style={{ display: 'flex', height: 'calc(100vh - 1.5rem)', fontFamily: FONT, width: '100%' }}>

      {/* LISTE CONVERSATIONS */}
      <div style={{
        width: '280px', flexShrink: 0,
        borderRight: '3px solid black',
        display: 'flex', flexDirection: 'column',
        backgroundColor: 'white'
      }}>
        <div style={{
          padding: '1rem 1.25rem', borderBottom: '3px solid black',
          backgroundColor: 'white'
        }}>
          <h2 style={{ margin: 0, fontSize: '1.2rem', fontFamily: FONT }}>Conversations</h2>
        </div>

        <div style={{ flex: 1, overflowY: 'auto' }}>
          {loading ? (
            <p style={{ padding: '1.5rem', textAlign: 'center', fontFamily: FONT }}>Chargement...</p>
          ) : conversations.length === 0 ? (
            <div style={{ padding: '2rem', textAlign: 'center' }}>
              <p style={{ color: '#555', fontFamily: FONT }}>Aucune conversation 💬</p>
              <button
                onClick={() => navigate('/friends')}
                style={{
                  marginTop: '1rem', padding: '0.5rem 1rem',
                  backgroundColor: 'white', border: '2px solid black',
                  borderRadius: '4px', cursor: 'pointer', fontFamily: FONT
                }}
              >
                Voir mes amis
              </button>
            </div>
          ) : (
            conversations.map(conv => (
              <button
                key={conv.id}
                onClick={() => handleSelectConv(conv)}
                style={{
                  width: '100%', padding: '0.85rem 1rem',
                  borderBottom: '2px solid black',
                  backgroundColor: selectedConv?.id === conv.id ? '#f0f0f0' : 'white',
                  color: '#000', border: 'none', borderBottom: '2px solid black', cursor: 'pointer',
                  textAlign: 'left', fontFamily: FONT,
                  display: 'flex', alignItems: 'center', gap: '0.75rem'
                }}
              >
                <div style={{
                  width: '40px', height: '40px', borderRadius: '50%',
                  border: '2px solid black', backgroundColor: '#f0f0f0',
                  display: 'flex', alignItems: 'center', justifyContent: 'center',
                  flexShrink: 0, overflow: 'hidden'
                }}>
                  {conv.avatar
                    ? <img src={conv.avatar} alt="" style={{ width: '100%', height: '100%', objectFit: 'cover' }} />
                    : '👤'}
                </div>
                <div style={{ flex: 1, overflow: 'hidden' }}>
                  <p style={{ fontWeight: 'bold', marginBottom: '2px' }}>{conv.username || 'Utilisateur'}</p>
                  <p style={{ fontSize: '0.8rem', color: '#666', whiteSpace: 'nowrap', overflow: 'hidden', textOverflow: 'ellipsis' }}>
                    {conv.lastMessage || '...'}
                  </p>
                </div>
              </button>
            ))
          )}
        </div>
      </div>

      {/* ZONE CHAT */}
      <div style={{ flex: 1, display: 'flex', flexDirection: 'column', backgroundColor: 'white' }}>
        {selectedConv ? (
          <>
            {/* Header */}
            <div style={{
              padding: '0.85rem 1.25rem', borderBottom: '3px solid black',
              backgroundColor: 'white', display: 'flex', alignItems: 'center', gap: '0.75rem'
            }}>
              <div style={{
                width: '40px', height: '40px', borderRadius: '50%',
                border: '2px solid black', backgroundColor: '#f0f0f0',
                display: 'flex', alignItems: 'center', justifyContent: 'center', overflow: 'hidden'
              }}>
                {selectedConv.avatar
                  ? <img src={selectedConv.avatar} alt="" style={{ width: '100%', height: '100%', objectFit: 'cover' }} />
                  : '👤'}
              </div>
              <span style={{ fontWeight: 'bold', fontSize: '1.1rem', fontFamily: FONT }}>
                {selectedConv.username || 'Utilisateur'}
              </span>
            </div>

            {/* Messages */}
            <div style={{ flex: 1, overflowY: 'auto', padding: '1rem', display: 'flex', flexDirection: 'column', gap: '0.6rem' }}>
              {messages.length === 0 ? (
                <p style={{ textAlign: 'center', color: '#888', marginTop: '2rem', fontFamily: FONT }}>
                  Aucun message. Commence la conversation !
                </p>
              ) : (
                messages.map(msg => {
                  const isOwn = msg.isOwn || msg.senderId === user?.id
                  return (
                    <div key={msg.id} style={{
                      alignSelf: isOwn ? 'flex-end' : 'flex-start',
                      maxWidth: '70%',
                      backgroundColor: isOwn ? '#e0e0e0' : '#f5f5f5',
                      border: '2px solid black',
                      borderRadius: isOwn ? '12px 12px 2px 12px' : '12px 12px 12px 2px',
                      padding: '0.5rem 0.85rem',
                      fontFamily: FONT, fontSize: '0.95rem'
                    }}>
                      {msg.content || msg.text}
                    </div>
                  )
                })
              )}
              <div ref={bottomRef} />
            </div>

            {/* Input */}
            <div style={{
              padding: '0.75rem 1rem', borderTop: '3px solid black',
              display: 'flex', gap: '0.75rem', backgroundColor: 'white'
            }}>
              <input
                type="text" value={messageText}
                onChange={e => setMessageText(e.target.value)}
                onKeyDown={e => e.key === 'Enter' && handleSend()}
                placeholder="Ton message..."
                style={{
                  flex: 1, padding: '0.6rem 1rem', fontFamily: FONT,
                  border: '2px solid black', borderRadius: '4px', fontSize: '1rem',
                  color: 'black', backgroundColor: 'white'
                }}
              />
              <button
                onClick={handleSend}
                style={{
                  padding: '0.6rem 1.25rem', backgroundColor: 'black',
                  color: '#00FEE5', border: '2px solid black', borderRadius: '4px',
                  cursor: 'pointer', fontFamily: FONT, fontWeight: 'bold', fontSize: '1rem'
                }}
              >
                Envoyer
              </button>
            </div>
          </>
        ) : (
          <div style={{
            flex: 1, display: 'flex', alignItems: 'center', justifyContent: 'center',
            color: '#888', fontFamily: FONT, fontSize: '1.1rem'
          }}>
            Selectionne une conversation →
          </div>
        )}
      </div>
    </div>
  )

  return (
    <AppLayout activeNav="messages">
      {mainContent}
    </AppLayout>
  )
}
