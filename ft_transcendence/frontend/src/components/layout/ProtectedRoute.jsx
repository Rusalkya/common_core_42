/**
 * @responsable clfouger
 * ROUTE PROTEGEE - Redirige vers login si non authentifie
 */

import { Navigate } from 'react-router-dom'
import { useAuth } from '../../context/AuthContext'

export const ProtectedRoute = ({ children }) => {
  const { user, isInitializing } = useAuth()

  // En attente de l'initialisation (verification du token)
  if (isInitializing) {
    return (
      <div style={{
        display: 'flex',
        alignItems: 'center',
        justifyContent: 'center',
        minHeight: '100vh',
        backgroundColor: 'var(--color-bg-primary)'
      }}>
        <div style={{ fontSize: '1.5rem', color: 'var(--color-text-secondary)' }}>
          ⏳ Chargement...
        </div>
      </div>
    )
  }

  // Si l'utilisateur n'est pas connecte, redirige vers login
  if (!user) {
    return <Navigate to="/login" replace />
  }

  return children
}
