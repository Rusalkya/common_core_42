import React, { useState, useEffect } from 'react';
import { useNavigate, Link } from 'react-router-dom';
import api from '../services/api';
import notifIcon from '../assets/logo/onglets/notif.png';
import bg from '../assets/background/background.png';
import logoGribouillit from '../assets/logo/page_title/logo_gribouillit.png';

export default function NotificationsPage() {
  const navigate = useNavigate();
  const [notifications, setNotifications] = useState([]);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState(null);

  const FONT = 'Gribouillit2.0, sans-serif';

  useEffect(() => {
    const load = async () => {
      try {
        setLoading(true);
        const res = await api.get('/notifications');
        setNotifications(res.data || []);
      } catch (err) {
        console.error('Notifications load error:', err);
        setError('Impossible de charger les notifications.');
      } finally {
        setLoading(false);
      }
    };
    load();
  }, []);

  const markAsRead = async (id) => {
    try {
      await api.patch(`/notifications/${id}/read`);
      setNotifications(prev =>
        prev.map(n => n.id === id ? { ...n, read: true } : n)
      );
    } catch (err) {
      console.error('Mark read error:', err);
    }
  };

  const markAllRead = async () => {
    try {
      await Promise.all(
        notifications.filter(n => !n.read).map(n => api.patch(`/notifications/${n.id}/read`))
      );
      setNotifications(prev => prev.map(n => ({ ...n, read: true })));
    } catch (err) {
      console.error('Mark all read error:', err);
    }
  };

  const unreadCount = notifications.filter(n => !n.read).length;

  const typeLabel = (type) => {
    const t = (type || '').toLowerCase();
    switch (t) {
      case 'like': return 'a aime ta publication';
      case 'comment': return 'a commente ta publication';
      case 'friend_request': return 't\'a envoye une demande d\'ami';
      case 'friend_accept':
      case 'friend_accepted': return 'a accepte ta demande d\'ami';
      case 'friend_removed': return 't\'a retire de sa liste d\'amis';
      case 'post_deleted': return 'a supprime une de ses publications';
      case 'repost': return 'a repartage ta publication';
      case 'message': return 't\'a envoye un message';
      case 'mention': return 't\'a mentionne';
      default: return type || 'Notification';
    }
  };

  const formatDate = (dateStr) => {
    if (!dateStr) return '';
    const d = new Date(dateStr);
    return d.toLocaleDateString('fr-FR', { day: '2-digit', month: 'short', hour: '2-digit', minute: '2-digit' });
  };

  return (
    <div style={{
      minHeight: '100vh',
      backgroundImage: `url(${bg})`,
      backgroundSize: 'cover',
      backgroundPosition: 'center',
      display: 'flex',
      flexDirection: 'column',
      alignItems: 'center',
      padding: '2rem',
      fontFamily: FONT
    }}>
      <div style={{ width: '100%', maxWidth: '700px' }}>
        {/* Logo cliquable → retour a la page d'accueil */}
        <Link to="/home" style={{ display: 'block', textAlign: 'center', marginBottom: '1rem' }}>
          <img src={logoGribouillit} alt="Gribouillit" style={{ height: '80px', cursor: 'pointer' }} />
        </Link>

        {/* HEADER */}
        <div style={{
          display: 'flex',
          alignItems: 'center',
          gap: '1rem',
          backgroundColor: 'white',
          border: '3px solid black',
          padding: '1rem 1.5rem',
          borderRadius: '4px',
          marginBottom: '1rem'
        }}>
          <button
            onClick={() => navigate('/home')}
            style={{
              background: 'none', border: '2px solid black',
              borderRadius: '4px', padding: '0.4rem 0.8rem',
              cursor: 'pointer', fontFamily: FONT, fontWeight: 'bold',
              fontSize: '1rem'
            }}
          >
            ← Retour
          </button>
          <img src={notifIcon} alt="Notifications" style={{ width: '36px', height: '36px' }} />
          <h1 style={{ margin: 0, fontSize: '1.8rem', color: '#000', flex: 1 }}>
            Notifications
          </h1>
          {unreadCount > 0 && (
            <span style={{
              backgroundColor: '#ff4444', color: 'white', border: '2px solid black',
              borderRadius: '999px', padding: '0.2rem 0.8rem',
              fontWeight: 'bold', fontSize: '1rem'
            }}>
              {unreadCount} non lues
            </span>
          )}
          {unreadCount > 0 && (
            <button
              onClick={markAllRead}
              style={{
                background: 'white', border: '2px solid black',
                borderRadius: '4px', padding: '0.4rem 0.8rem',
                cursor: 'pointer', fontFamily: FONT, fontWeight: 'bold',
                fontSize: '0.9rem', color: '#000'
              }}
            >
              Tout lire
            </button>
          )}
        </div>

        {/* CONTENT */}
        <div style={{
          backgroundColor: 'white',
          border: '3px solid black',
          borderRadius: '4px',
          overflow: 'hidden'
        }}>
          {loading && (
            <p style={{ textAlign: 'center', padding: '2rem', fontFamily: FONT }}>
              Chargement...
            </p>
          )}

          {error && (
            <p style={{ textAlign: 'center', padding: '2rem', color: '#dc2626', fontFamily: FONT }}>
              ⚠️ {error}
            </p>
          )}

          {!loading && !error && notifications.length === 0 && (
            <div style={{ textAlign: 'center', padding: '3rem' }}>
              <p style={{ fontSize: '1.2rem', fontFamily: FONT, color: '#555' }}>
                Aucune notification pour l'instant
              </p>
            </div>
          )}

          {!loading && notifications.map((notif, idx) => (
            <div
              key={notif.id || idx}
              onClick={() => !notif.read && markAsRead(notif.id)}
              style={{
                display: 'flex',
                alignItems: 'center',
                gap: '1rem',
                padding: '1rem 1.5rem',
                borderBottom: idx < notifications.length - 1 ? '2px solid black' : 'none',
                backgroundColor: notif.read ? 'white' : '#fffde7',
                cursor: notif.read ? 'default' : 'pointer',
                transition: 'background-color 0.2s'
              }}
            >
              {/* Avatar */}
              <div style={{
                width: '48px', height: '48px', borderRadius: '50%',
                border: '2px solid black', overflow: 'hidden', flexShrink: 0,
                backgroundColor: '#f0f0f0', display: 'flex', alignItems: 'center', justifyContent: 'center'
              }}>
                {notif.fromUser?.avatar ? (
                  <img src={notif.fromUser.avatar} alt="" style={{ width: '100%', height: '100%', objectFit: 'cover' }} />
                ) : (
                  <span style={{ fontSize: '1.4rem' }}>👤</span>
                )}
              </div>

              {/* Content */}
              <div style={{ flex: 1 }}>
                <p style={{ margin: 0, fontFamily: FONT, fontSize: '1rem', color: '#000' }}>
                  <strong>{notif.fromUser?.username || 'Quelqu\'un'}</strong>{' '}
                  {typeLabel(notif.type)}
                </p>
                {notif.createdAt && (
                  <p style={{ margin: '0.2rem 0 0', fontSize: '0.8rem', color: '#666', fontFamily: FONT }}>
                    {formatDate(notif.createdAt)}
                  </p>
                )}
              </div>

              {/* Unread indicator */}
              {!notif.read && (
                <div style={{
                  width: '12px', height: '12px', borderRadius: '50%',
                  backgroundColor: '#ff4444', border: '2px solid black', flexShrink: 0
                }} />
              )}
            </div>
          ))}
        </div>
      </div>
    </div>
  );
}
