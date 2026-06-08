import React from 'react';
import { BrowserRouter, Routes, Route, Navigate } from 'react-router-dom';
import { AuthProvider } from './context/AuthContext';
import { NotificationProvider } from './context/NotificationContext';
import { SocketProvider, useSocket } from './context/SocketContext';

import RegisterPage from './pages/RegisterPage';
import LoginPage from './pages/LoginPage';
import AvatarStep from './pages/AvatarStep';
import PrivacyPolicy from './pages/PrivacyPolicy';
import TermsOfService from './pages/TermsOfService';
import ProfileModifications from './pages/ProfileModifications';
import { HomePage } from './pages/HomePage';
import { ProfilePage } from './pages/MyProfilePage';
import { FriendsPage } from './pages/FriendsPage';
import { MessagesPage } from './pages/MessagesPage';
import DrawPage from './pages/DrawPage';
import NotificationsPage from './pages/NotificationsPage';

// Overlay de toasts pour les notifications temps reel (likes, commentaires, amis)
const LiveNotifToasts = () => {
  const { liveNotifications, clearLiveNotification } = useSocket()
  if (!liveNotifications.length) return null
  return (
    <div style={{
      position: 'fixed', bottom: '24px', right: '24px',
      zIndex: 9999, display: 'flex', flexDirection: 'column', gap: '10px',
      pointerEvents: 'none',
    }}>
      {liveNotifications.map(n => (
        <div
          key={n.id}
          style={{
            backgroundColor: 'white', border: '3px solid black',
            borderRadius: '8px', padding: '12px 20px',
            fontFamily: 'Gribouillit2.0, sans-serif',
            fontSize: '1rem', boxShadow: '4px 4px 0 black',
            display: 'flex', alignItems: 'center', gap: '10px',
            pointerEvents: 'auto', cursor: 'pointer',
            minWidth: '240px',
          }}
          onClick={() => clearLiveNotification(n.id)}
        >
          <span>{n.message}</span>
        </div>
      ))}
    </div>
  )
}

function App() {
  return (
    <AuthProvider>
      <SocketProvider>
        <NotificationProvider>
          <BrowserRouter>
            <LiveNotifToasts />
            <Routes>
              <Route path="/" element={<Navigate to="/register" replace />} />
              <Route path="/register" element={<RegisterPage />} />
              <Route path="/login" element={<LoginPage />} />
              <Route path="/avatar-step" element={<AvatarStep />} />
              <Route path="/home" element={<HomePage />} />
              <Route path="/profile/:userId" element={<ProfilePage />} />
              <Route path="/profile-modifications" element={<ProfileModifications />} />
              <Route path="/friends" element={<FriendsPage />} />
              <Route path="/messages" element={<MessagesPage />} />
              <Route path="/draw" element={<DrawPage />} />
              <Route path="/notifications" element={<NotificationsPage />} />
              <Route path="/privacy" element={<PrivacyPolicy />} />
              <Route path="/terms" element={<TermsOfService />} />
              <Route path="*" element={<h1 style={{color:'black'}}>404 - Page not found</h1>} />
            </Routes>
          </BrowserRouter>
        </NotificationProvider>
      </SocketProvider>
    </AuthProvider>
  );
}

export default App;
