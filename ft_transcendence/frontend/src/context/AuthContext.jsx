/**
 * @responsable clfouger
 * CONTEXTE D'AUTHENTIFICATION
 * 
 * Gere : utilisateur connecte, token JWT, login, logout
 */

import { createContext, useContext, useState, useEffect } from 'react'

const AuthContext = createContext(null)

export const AuthProvider = ({ children }) => {
  const [user, setUser] = useState(null)
  const [token, setToken] = useState(localStorage.getItem('token') || null)
  const [loading, setLoading] = useState(false)
  const [error, setError] = useState(null)
  const [isInitializing, setIsInitializing] = useState(true)

  // Verifier le token au chargement
  useEffect(() => {
    const init = async () => {
      if (token) {
        try {
          const response = await fetch(`${import.meta.env.VITE_API_URL}/auth/me`, {
            headers: { Authorization: `Bearer ${token}` }
          })
          if (response.ok) {
            const json = await response.json()
            setUser(json.data || json)
          } else if (response.status === 401) {
            logout()
          }
        } catch (err) {
          // Network error (not an auth failure) — keep the token and stay logged in
          console.error('Token validation error:', err)
        }
      }
      setIsInitializing(false)
    }
    init()
  }, [])

  const login = async (email, password) => {
    setLoading(true)
    setError(null)
    try {
      const response = await fetch(`${import.meta.env.VITE_API_URL}/auth/login`, {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ email, password })
      })
      const data = await response.json()
      if (response.ok) {
        const payload = data.data || data
        setToken(payload.access_token)
        setUser(payload.user)
        localStorage.setItem('token', payload.access_token)
        return true
      } else {
        setError(data.message || (data.data && data.data.message) || 'Erreur de connexion')
        return false
      }
    } catch (err) {
      setError(err.message)
      return false
    } finally {
      setLoading(false)
    }
  }

  const register = async (email, username, password) => {
    setLoading(true)
    setError(null)
    try {
      const response = await fetch(`${import.meta.env.VITE_API_URL}/auth/register`, {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ email, username, password })
      })
      const data = await response.json()
      if (response.ok) {
        const payload = data.data || data
        setToken(payload.access_token)
        setUser(payload.user)
        localStorage.setItem('token', payload.access_token)
        return true
      } else {
        setError(data.message || (data.data && data.data.message) || 'Erreur d\'inscription')
        return false
      }
    } catch (err) {
      setError(err.message)
      return false
    } finally {
      setLoading(false)
    }
  }

  const refreshUser = async () => {
    const storedToken = localStorage.getItem('token')
    if (!storedToken) return
    try {
      const response = await fetch(`${import.meta.env.VITE_API_URL}/users/me`, {
        headers: { Authorization: `Bearer ${storedToken}` }
      })
      if (response.ok) {
        const json = await response.json()
        setUser(json.data || json)
      }
    } catch (err) {
      console.error('refreshUser error:', err)
    }
  }

  const logout = () => {
    setUser(null)
    setToken(null)
    localStorage.removeItem('token')
  }

  return (
    <AuthContext.Provider value={{
      user,
      token,
      loading,
      error,
      isAuthenticated: !!user,
      isInitializing,
      login,
      register,
      logout,
      refreshUser
    }}>
      {children}
    </AuthContext.Provider>
  )
}

export const useAuth = () => {
  const context = useContext(AuthContext)
  if (!context) {
    throw new Error('useAuth doit etre utilise dans AuthProvider')
  }
  return context
}
