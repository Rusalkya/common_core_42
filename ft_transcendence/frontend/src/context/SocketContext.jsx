/**
 * @responsable clfouger
 * CONTEXTE WEBSOCKET
 * 
 * Gere la connexion Socket.io partagee dans toute l'app.
 * Connecte au namespace /chat (ChatGateway).
 * Ecoute les evenements 'notification' envoyes par le backend.
 */

import { createContext, useContext, useEffect, useState, useCallback } from 'react'
import { io } from 'socket.io-client'
import { useAuth } from './AuthContext'

const SocketContext = createContext(null)

export const SocketProvider = ({ children }) => {
  const [socket, setSocket] = useState(null)
  const [isConnected, setIsConnected] = useState(false)
  const [liveNotifications, setLiveNotifications] = useState([])
  const [onlineUsers, setOnlineUsers] = useState(new Set())
  const { token, user } = useAuth()

  const clearLiveNotification = useCallback((id) => {
    setLiveNotifications(prev => prev.filter(n => n.id !== id))
  }, [])

  const isUserOnline = useCallback((userId) => {
    return onlineUsers.has(Number(userId))
  }, [onlineUsers])

  useEffect(() => {
    if (!token) {
      setSocket(null)
      setIsConnected(false)
      return
    }

    // Connecte au namespace /chat ou vit le ChatGateway
    const newSocket = io(`${import.meta.env.VITE_WS_URL || window.location.origin}/chat`, {
      auth: { token },
      reconnection: true,
      reconnectionDelay: 1000,
      reconnectionDelayMax: 5000,
      reconnectionAttempts: 5,
    })

    newSocket.on('connect', () => {
      setIsConnected(true)
      // Rejoindre la room personnelle pour les notifications
      if (user?.id) {
        newSocket.emit('authenticate', { userId: user.id })
      }
    })

    newSocket.on('disconnect', () => {
      setIsConnected(false)
      setOnlineUsers(new Set())
    })

    // Liste initiale des users en ligne (recue apres authenticate)
    newSocket.on('onlineUsersList', (data) => {
      setOnlineUsers(new Set((data.userIds || []).map(Number)))
    })

    // Quelqu'un vient de se connecter
    newSocket.on('userOnline', (data) => {
      setOnlineUsers(prev => {
        const next = new Set(prev)
        next.add(Number(data.userId))
        return next
      })
    })

    // Quelqu'un vient de se deconnecter
    newSocket.on('userOffline', (data) => {
      setOnlineUsers(prev => {
        const next = new Set(prev)
        next.delete(Number(data.userId))
        return next
      })
    })

    // Reception des notifications temps reel (like, commentaire, demande d'ami, etc.)
    newSocket.on('notification', (data) => {
      const notif = {
        id: Date.now(),
        message: data.message || 'Nouvelle notification',
        type: data.type || 'info',
      }
      setLiveNotifications(prev => [...prev, notif])
      // Auto-dismiss apres 5 secondes
      setTimeout(() => {
        setLiveNotifications(prev => prev.filter(n => n.id !== notif.id))
      }, 5000)
    })

    setSocket(newSocket)

    return () => {
      newSocket.disconnect()
    }
  }, [token, user?.id])

  return (
    <SocketContext.Provider value={{ socket, isConnected, liveNotifications, clearLiveNotification, onlineUsers, isUserOnline }}>
      {children}
    </SocketContext.Provider>
  )
}

export const useSocket = () => {
  const context = useContext(SocketContext)
  if (!context) {
    throw new Error('useSocket doit etre utilise dans SocketProvider')
  }
  return context
}
