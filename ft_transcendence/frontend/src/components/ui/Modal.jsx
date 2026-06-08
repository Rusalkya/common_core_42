/**
 * @responsable clfouger
 * COMPOSANT MODAL - Fenetre modale reutilisable
 */

import { useEffect } from 'react'

export const Modal = ({ 
  isOpen, 
  onClose, 
  title, 
  children, 
  className = '',
  size = 'medium'
}) => {
  useEffect(() => {
    if (isOpen) {
      document.body.style.overflow = 'hidden'
    }
    return () => {
      document.body.style.overflow = 'auto'
    }
  }, [isOpen])

  if (!isOpen) return null

  const handleBackdropClick = (e) => {
    if (e.target === e.currentTarget) {
      onClose()
    }
  }

  return (
    <div className="modal-backdrop" onClick={handleBackdropClick}>
      <div className={`modal ${className}`} style={{ maxWidth: size === 'large' ? '1000px' : '600px' }}>
        {title && (
          <div className="modal-header">
            <h2 style={{ fontSize: 'var(--font-size-xl)', fontWeight: 'var(--font-weight-bold)' }}>
              {title}
            </h2>
            <button className="modal-close" onClick={onClose}>✕</button>
          </div>
        )}
        <div style={{ padding: 'var(--spacing-lg)' }}>
          {children}
        </div>
      </div>
    </div>
  )
}
