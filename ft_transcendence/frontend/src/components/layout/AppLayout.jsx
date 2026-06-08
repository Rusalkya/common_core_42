/**
 * AppLayout - Mise en page partagee pour toutes les pages post-connexion
 * Sidebar identique a la homepage + background papier quadrille
 */

import React, { useState, useEffect } from 'react';
import { useNavigate, Link } from 'react-router-dom';
import { useAuth } from '../../context/AuthContext';
import { useNotification } from '../../context/NotificationContext';
import '../../styles/homepage.css';

import logoGribouillit from '../../assets/logo/page_title/logo_gribouillit.png';
import brushIcon from '../../assets/logo/canva tools/brush.png';
import notificationsIcon from '../../assets/logo/onglets/notif.png';
import notificationsIconNotif from '../../assets/logo/onglets/notif_1.png';
import messagesIcon from '../../assets/logo/onglets/private_messages.png';
import messagesIconNotif from '../../assets/logo/onglets/private_messages_notif.png';
import friendsIcon from '../../assets/logo/onglets/friends.png';
import settingsIcon from '../../assets/logo/onglets/settings.png';
import img1 from '../../assets/images/img1.png';
import img2 from '../../assets/images/img2.png';
import img3 from '../../assets/images/img3.png';
import img4 from '../../assets/images/img4.png';
import img5 from '../../assets/images/img5.png';

const avatars = [img1, img2, img3, img4, img5];

/**
 * @param {object} props
 * @param {React.ReactNode} props.children - contenu principal (colonne du milieu)
 * @param {React.ReactNode} [props.rightPanel] - panneau droit optionnel (remplace le chat)
 * @param {string} [props.activeNav] - 'notifications'|'messages'|'friends'|'settings'|'profile'
 */
export default function AppLayout({ children, rightPanel, activeNav }) {
  const navigate = useNavigate();
  const { user } = useAuth();
  const { unreadCount } = useNotification();
  const [userAvatar, setUserAvatar] = useState(null);

  useEffect(() => {
    if (user?.avatar) setUserAvatar(user.avatar);
    else {
      const idx = localStorage.getItem('selectedAvatar');
      if (idx !== null) setUserAvatar(avatars[parseInt(idx)]);
    }
  }, [user]);

  const navItems = [
    { id: 'profile',       icon: null,              label: 'mon profil',    path: `/profile/${user?.id}` },
    { id: 'notifications', icon: unreadCount > 0 ? notificationsIconNotif : notificationsIcon,  label: 'notifications', path: '/notifications' },
    { id: 'messages',      icon: unreadCount > 0 ? messagesIconNotif : messagesIcon,       label: 'mes messages',  path: '/messages' },
    { id: 'friends',       icon: friendsIcon,        label: 'mes amis',      path: '/friends' },
    { id: 'settings',      icon: settingsIcon,       label: 'parametres',    path: '/profile-modifications' },
  ];

  return (
    <div className="homepage" style={{ gridTemplateColumns: rightPanel ? '300px 1fr 360px' : '300px 1fr' }}>
      {/* SIDEBAR */}
      <aside className="homepage-sidebar">
        {/* Logo cliquable → retour a la page d'accueil */}
        <Link to="/home" style={{ display: 'block', textAlign: 'center' }}>
          <img
            src={logoGribouillit}
            alt="Gribouillit"
            style={{ width: 'auto', height: '100px', cursor: 'pointer' }}
          />
        </Link>

        <nav className="sidebar-nav">
          {navItems.map(({ id, icon, label, path }) => (
            <button
              key={id}
              className="nav-btn"
              onClick={() => navigate(path)}
              style={activeNav === id ? { background: '#B5FF6B', border: '3px solid black' } : {}}
            >
              {id === 'profile' ? (
                userAvatar ? (
                  <img src={userAvatar} alt="avatar" style={{ width: '32px', height: '32px', borderRadius: '50%', objectFit: 'cover', border: '2px solid black', flexShrink: 0 }} />
                ) : (
                  <span style={{ fontSize: '1.5rem', lineHeight: 1 }}>👤</span>
                )
              ) : (
                <div style={{ position: 'relative', display: 'flex', alignItems: 'center' }}>
                  <img src={icon} alt={label} className="nav-icon" />
                  {id === 'notifications' && unreadCount > 0 && (
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
              )}
              <span>{label}</span>
            </button>
          ))}
        </nav>

        <button className="btn-tweet" onClick={() => navigate('/draw')}
          style={{ marginTop: '1rem' }}>
          <img src={brushIcon} alt="Pinceau" className="tweet-icon" />
          <span>gribouiller !</span>
        </button>
      </aside>

      {/* CONTENU PRINCIPAL */}
      <main className="homepage-main" style={{ minHeight: '100vh', display: 'flex', flexDirection: 'column' }}>
        <div style={{ flex: 1 }}>{children}</div>
        <footer style={{
          borderTop: '2px solid black', padding: '0.75rem 1.5rem',
          display: 'flex', gap: '1.5rem', justifyContent: 'center',
          fontFamily: 'Gribouillit2.0, sans-serif', fontSize: '0.8rem'
        }}>
          <a href="/privacy" style={{ color: '#555', textDecoration: 'none' }}>Politique de confidentialite</a>
          <a href="/terms" style={{ color: '#555', textDecoration: 'none' }}>Conditions d'utilisation</a>
        </footer>
      </main>

      {/* PANNEAU DROIT (optionnel) */}
      {rightPanel && (
        <aside style={{ minHeight: '100vh' }}>
          {rightPanel}
        </aside>
      )}
    </div>
  );
}
