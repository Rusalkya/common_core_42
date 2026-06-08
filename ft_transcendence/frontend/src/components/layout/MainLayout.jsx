/**
 * @responsable clfouger
 * LAYOUT PRINCIPAL - Navigation et structure
 */

import { useState } from 'react'
import { useAuth } from '../../context/AuthContext'
import { Button } from '../ui/Button'
import { DrawingModal } from '../drawing/DrawingModal'

export const MainLayout = ({ children, onDrawingCreated }) => {
  const { user, logout } = useAuth()
  const [isDrawingModalOpen, setIsDrawingModalOpen] = useState(false)

  return (
    <div style={{ display: 'flex', minHeight: '100vh', width: '100%' }}>
      {/* Sidebar Navigation */}
      <nav style={{
        width: '250px',
        borderRight: '1px solid var(--color-border)',
        padding: 'var(--spacing-lg)',
        backgroundColor: 'var(--color-bg-primary)',
        overflowY: 'auto'
      }}>
        {/* Logo */}
        <div style={{
          fontSize: 'var(--font-size-2xl)',
          fontWeight: 'var(--font-weight-bold)',
          marginBottom: 'var(--spacing-2xl)',
          color: 'var(--color-primary)'
        }}>
          🎨 DrawTweet
        </div>

        {/* Menu */}
        <div style={{ display: 'flex', flexDirection: 'column', gap: 'var(--spacing-md)' }}>
          <NavLink href="/home" icon="🏠">Accueil</NavLink>
          <NavLink href="/profile" icon="👤">Mon profil</NavLink>
          <NavLink href="/friends" icon="👥">Amis</NavLink>
          <NavLink href="/chat" icon="💬">Messages</NavLink>
          <NavLink href="/settings" icon="⚙️">Parametres</NavLink>
        </div>

        {/* Bouton creer dessin */}
        <Button
          variant="primary"
          onClick={() => setIsDrawingModalOpen(true)}
          style={{
            width: '100%',
            marginTop: 'var(--spacing-2xl)',
            display: 'flex',
            alignItems: 'center',
            justifyContent: 'center',
            gap: 'var(--spacing-md)'
          }}
        >
          ✏️ Creer un dessin
        </Button>

        {/* User info et logout */}
        {user && (
          <div style={{
            marginTop: 'auto',
            paddingTop: 'var(--spacing-lg)',
            borderTop: '1px solid var(--color-border)',
            display: 'flex',
            flexDirection: 'column',
            gap: 'var(--spacing-md)'
          }}>
            <div style={{ fontSize: 'var(--font-size-sm)' }}>
              <strong>{user.username}</strong>
              <div style={{ color: 'var(--color-text-tertiary)' }}>@{user.username}</div>
            </div>
            <Button
              variant="secondary"
              size="small"
              onClick={logout}
              style={{ width: '100%' }}
            >
              Deconnexion
            </Button>
          </div>
        )}
      </nav>

      {/* Main Content */}
      <div style={{ flex: 1, overflowY: 'auto' }}>
        {children}
      </div>

      {/* Drawing Modal */}
      <DrawingModal
        isOpen={isDrawingModalOpen}
        onClose={() => setIsDrawingModalOpen(false)}
        onPostCreated={() => {
          setIsDrawingModalOpen(false)
          onDrawingCreated?.()
        }}
      />
    </div>
  )
}

const NavLink = ({ href, icon, children }) => (
  <a
    href={href}
    style={{
      display: 'flex',
      alignItems: 'center',
      gap: 'var(--spacing-md)',
      padding: 'var(--spacing-md) var(--spacing-lg)',
      borderRadius: 'var(--border-radius-md)',
      color: 'var(--color-text-primary)',
      textDecoration: 'none',
      transition: 'background-color var(--transition-fast)',
      cursor: 'pointer'
    }}
    onMouseEnter={(e) => e.target.style.backgroundColor = 'var(--color-bg-secondary)'}
    onMouseLeave={(e) => e.target.style.backgroundColor = 'transparent'}
  >
    <span style={{ fontSize: '18px' }}>{icon}</span>
    {children}
  </a>
)
