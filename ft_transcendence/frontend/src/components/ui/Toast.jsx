/**
 * @responsable clfouger
 * COMPOSANT TOAST - Notifications toast
 */

import { useNotification } from '../../context/NotificationContext'

export const Toast = () => {
  const { notifications, removeNotification } = useNotification()

  return (
    <div style={{ position: 'fixed', bottom: 'var(--spacing-lg)', right: 'var(--spacing-lg)', zIndex: 'var(--z-tooltip)' }}>
      {notifications.map(notification => (
        <div
          key={notification.id}
          className={`toast toast-${notification.type}`}
          style={{ marginTop: 'var(--spacing-md)' }}
        >
          <div style={{ display: 'flex', justifyContent: 'space-between', alignItems: 'center', gap: 'var(--spacing-lg)' }}>
            <span>{notification.message}</span>
            <button
              onClick={() => removeNotification(notification.id)}
              style={{ background: 'none', border: 'none', color: 'inherit', cursor: 'pointer', fontSize: '18px' }}
            >
              ✕
            </button>
          </div>
        </div>
      ))}
    </div>
  )
}
