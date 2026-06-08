/**
 * @responsable clfouger
 * CONTEXTE NOTIFICATIONS
 * 
 * Gere les notifications en temps reel + polling du compteur non lu
 */

import { createContext, useContext, useState, useCallback, useEffect, useRef } from 'react'
import api from '../services/api'
import { useAuth } from './AuthContext'

const NotificationContext = createContext(null)

export const NotificationProvider = ({ children }) => {
  const [notifications, setNotifications] = useState([])
  const [unreadCount, setUnreadCount] = useState(0)
  const prevCountRef = useRef(-1)
  const { token } = useAuth()

  // Polling du nombre de notifications non lues (toutes les 20 secondes)
  useEffect(() => {
    if (!token) return
    const poll = async () => {
      try {
        const res = await api.get('/notifications/unread')
        const count = res.data?.count ?? 0
        setUnreadCount(count)
        prevCountRef.current = count
      } catch {
        // ignore si non connecte
      }
    }
    poll()
    const interval = setInterval(poll, 20000)
    return () => clearInterval(interval)
  }, [token])

  const addNotification = useCallback((message, type = 'info', duration = 3000) => {
    const id = Date.now()
    const notification = { id, message, type }
    
    setNotifications(prev => [...prev, notification])

    if (duration > 0) {
      setTimeout(() => {
        removeNotification(id)
      }, duration)
    }

    return id
  }, [])

  const removeNotification = useCallback((id) => {
    setNotifications(prev => prev.filter(n => n.id !== id))
  }, [])

  const success = (message, duration) => addNotification(message, 'success', duration)
  const error = (message, duration) => addNotification(message, 'error', duration)
  const warning = (message, duration) => addNotification(message, 'warning', duration)
  const info = (message, duration) => addNotification(message, 'info', duration)

  return (
    <NotificationContext.Provider value={{
      notifications,
      unreadCount,
      setUnreadCount,
      addNotification,
      removeNotification,
      success,
      error,
      warning,
      info
    }}>
      {children}
    </NotificationContext.Provider>
  )
}

export const useNotification = () => {
  const context = useContext(NotificationContext)
  if (!context) {
    throw new Error('useNotification doit etre utilise dans NotificationProvider')
  }
  return context
}
