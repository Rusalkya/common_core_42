import React, { useState } from 'react';
import { useNavigate } from 'react-router-dom';
import bg from '../assets/background/background.png';
import logo from '../assets/logo/page_title/logo_gribouillit.png';
import { userService } from '../services/userService';
import { useAuth } from '../context/AuthContext';

import img1 from '../assets/images/img1.png';
import img2 from '../assets/images/img2.png';
import img3 from '../assets/images/img3.png';
import img4 from '../assets/images/img4.png';
import img5 from '../assets/images/img5.png';

export default function AvatarStep() {
  const [selectedAvatar, setSelectedAvatar] = useState(null);
  const [saving, setSaving] = useState(false);
  const navigate = useNavigate();
  const { refreshUser } = useAuth();

  const ASSETS = {
    avatars: [img1, img2, img3, img4, img5],
    fontFamily: 'Gribouillit2.0, sans-serif'
  };

  return (
    <div style={{
      position: 'fixed',
      inset: 0,
      display: 'flex',
      alignItems: 'center',
      justifyContent: 'center',
      backgroundImage: `url(${bg})`,
      backgroundSize: 'cover',
      backgroundPosition: 'center',
      fontFamily: ASSETS.fontFamily
    }}>

      {/* LOGO */}
      <div style={{
        position: 'absolute',
        top: '40px',
        left: '50%',
        transform: 'translateX(-50%)',
        width: '500px',
        textAlign: 'center'
      }}>
        <img src={logo} alt="Gribouillit" style={{ maxWidth: '100%', height: 'auto', maxHeight: '280px' }} />
      </div>

      {/* MAIN */}
      <div style={{
        width: '900px',
        border: '4px solid black',
        backgroundColor: 'white',
        padding: '3rem',
        textAlign: 'center'
      }}>

        <h1 style={{ fontSize: '2.5rem', marginBottom: '2rem', position: 'relative', zIndex: 10, color: 'black' }}>
          Choisi un avatar
        </h1>

        {/* AVATARS */}
        <div style={{
          display: 'flex',
          justifyContent: 'center',
          gap: '2rem',
          marginBottom: '3rem'
        }}>
          {ASSETS.avatars.map((avatar, i) => (
            <div
              key={i}
              onClick={() => setSelectedAvatar(i)}
              style={{
                width: '120px',
                height: '120px',
                borderRadius: '50%',
                backgroundColor: 'white',
                display: 'flex',
                alignItems: 'center',
                justifyContent: 'center',
                cursor: 'pointer',
                border: selectedAvatar === i ? '4px solid black' : '2px solid black',
                overflow: 'hidden'
              }}
            >
              <img src={avatar} style={{ width: '100%', height: '100%', objectFit: 'cover' }} />
            </div>
          ))}
        </div>

        <button
          onClick={async () => {
            if (selectedAvatar === null) {
              alert('Veuillez selectionner un avatar');
              return;
            }
            setSaving(true);
            localStorage.setItem('selectedAvatar', selectedAvatar);
            try {
              const res = await fetch(ASSETS.avatars[selectedAvatar]);
              const blob = await res.blob();
              const file = new File([blob], 'avatar.png', { type: 'image/png' });
              await userService.uploadAvatar(file);
              await refreshUser();
            } catch (err) {
              console.error('Avatar save error:', err);
            } finally {
              setSaving(false);
              navigate('/home');
            }
          }}
          disabled={saving}
          style={{
            marginTop: '2rem',
            padding: '0.75rem 2rem',
            fontSize: '1rem',
            backgroundColor: saving ? '#555' : 'black',
            border: '2px solid black',
            borderRadius: '4px',
            cursor: saving ? 'not-allowed' : 'pointer',
            fontWeight: 'bold',
            color: '#00FEE5'
          }}
        >
          {saving ? 'Sauvegarde...' : 'Continuer'}
        </button>

        <p style={{ marginTop: '2rem', textAlign: 'center', color: 'black' }}>
          Deja inscrit ? <a href="/login" style={{ color: '#00FEE5', fontWeight: '600', textDecoration: 'none' }}>Je me connecte</a>
        </p>
      </div>
    </div>
  );
}
