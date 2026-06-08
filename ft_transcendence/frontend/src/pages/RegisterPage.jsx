import React, { useState } from 'react';
import { useNavigate } from 'react-router-dom';
import bg from '../assets/background/background.png';
import logo from '../assets/logo/page_title/logo_gribouillit.png';
import '../styles/globals.css';
import { useAuth } from '../context/AuthContext';

export default function RegisterPage() {
  const navigate = useNavigate();
  const { register, error: authError, loading } = useAuth();
  const [formData, setFormData] = useState({
    username: '',
    email: '',
    password: '',
    confirmPassword: ''
  });

  const [errors, setErrors] = useState({});

  const ASSETS = {
    logoText: 'logo du site',
    pageTitle: 'S\'inscrire',
    borderColor: 'border-black',
    buttonColor: 'bg-black',
    buttonHoverColor: 'hover:bg-gray-800',
    fontFamily: 'Gribouillit2.0, sans-serif'
  };

  const handleChange = (e) => {
    const { name, value } = e.target;
    setFormData(prev => ({
      ...prev,
      [name]: value
    }));
  };

  const validateForm = () => {
    const newErrors = {};
    if (!formData.username.trim()) newErrors.username = 'Required';
    if (!formData.email.trim()) newErrors.email = 'Required';
    if (formData.password.length < 8) newErrors.password = 'Min 8 caracteres';
    if (formData.password !== formData.confirmPassword) newErrors.confirmPassword = 'Passwords do not match';
    return newErrors;
  };

  const handleSubmit = async (e) => {
    e.preventDefault();
    const newErrors = validateForm();
    if (Object.keys(newErrors).length > 0) {
      setErrors(newErrors);
      return;
    }
    localStorage.setItem('signupUsername', formData.username);
    localStorage.removeItem('avatarDrawing');
    localStorage.removeItem('isDrawingMode');
    localStorage.removeItem('selectedAvatar');
    const success = await register(formData.email, formData.username, formData.password);
    if (success) {
      navigate('/avatar-step');
    }
  };

  return (
    <div 
      style={{
        position: 'fixed',
        top: 0,
        left: 0,
        right: 0,
        bottom: 0,
        width: '100vw',
        height: '100vh',
        display: 'flex',
        alignItems: 'center',
        justifyContent: 'center',
        backgroundImage: `url(${bg})`,
        backgroundSize: 'cover',
        backgroundPosition: 'center',
        backgroundRepeat: 'no-repeat',
        overflow: 'hidden',
        fontFamily: ASSETS.fontFamily
      }}
    >
      <style>{`
        @keyframes float {
          0%, 100% { transform: translateY(0px); }
          50% { transform: translateY(-20px); }
        }
        body {
          font-family: ${ASSETS.fontFamily};
        }
      `}</style>

      <div style={{ width: '100%', maxWidth: '650px', zIndex: 10, padding: '1rem' }}>
        <div style={{
          textAlign: 'center',
          marginBottom: '1.5rem',
          fontFamily: ASSETS.fontFamily
        }}>
          <img src={logo} alt="Gribouillit" style={{ maxWidth: '100%', height: 'auto', maxHeight: '280px' }} />
        </div>

        <div style={{
          border: '4px solid black',
          borderRadius: '8px',
          padding: '2rem',
          backgroundColor: 'rgba(255, 255, 255, 0.97)',
          fontFamily: ASSETS.fontFamily
        }}>
          <h1 style={{
            fontSize: '1.875rem',
            fontWeight: 'bold',
            textAlign: 'center',
            marginBottom: '2rem',
            color: 'black',
            fontFamily: ASSETS.fontFamily
          }}>
            {ASSETS.pageTitle}
          </h1>
          
          <form onSubmit={handleSubmit} style={{ display: 'flex', flexDirection: 'column', gap: '1.25rem' }}>
            <div>
              <input
                type="text"
                name="username"
                value={formData.username}
                onChange={handleChange}
                style={{
                  width: '100%',
                  padding: '0.75rem 1rem',
                  border: '2px solid #d1d5db',
                  borderRadius: '0.5rem',
                  outline: 'none',
                  color: '#111827',
                  fontSize: '1.125rem',
                  fontFamily: ASSETS.fontFamily
                }}
                placeholder="Nom d'utilisateur"
              />
              {errors.username && <p style={{ color: '#dc2626', fontSize: '0.75rem', marginTop: '0.25rem' }}>{errors.username}</p>}
            </div>

            <div>
              <input
                type="email"
                name="email"
                value={formData.email}
                onChange={handleChange}
                style={{
                  width: '100%',
                  padding: '0.75rem 1rem',
                  border: '2px solid #d1d5db',
                  borderRadius: '0.5rem',
                  outline: 'none',
                  color: '#111827',
                  fontSize: '1.125rem',
                  fontFamily: ASSETS.fontFamily
                }}
                placeholder="Email"
              />
              {errors.email && <p style={{ color: '#dc2626', fontSize: '0.75rem', marginTop: '0.25rem' }}>{errors.email}</p>}
            </div>

            <div>
              <input
                type="password"
                name="password"
                value={formData.password}
                onChange={handleChange}
                style={{
                  width: '100%',
                  padding: '0.75rem 1rem',
                  border: '2px solid #d1d5db',
                  borderRadius: '0.5rem',
                  outline: 'none',
                  color: '#111827',
                  fontSize: '1.125rem',
                  fontFamily: ASSETS.fontFamily
                }}
                placeholder="Mot de passe"
              />
              {errors.password && <p style={{ color: '#dc2626', fontSize: '0.75rem', marginTop: '0.25rem' }}>{errors.password}</p>}
            </div>

            <div>
              <input
                type="password"
                name="confirmPassword"
                value={formData.confirmPassword}
                onChange={handleChange}
                style={{
                  width: '100%',
                  padding: '0.75rem 1rem',
                  border: '2px solid #d1d5db',
                  borderRadius: '0.5rem',
                  outline: 'none',
                  color: '#111827',
                  fontSize: '1.125rem',
                  fontFamily: ASSETS.fontFamily
                }}
                placeholder="Confirmer le mot de passe"
              />
              {errors.confirmPassword && <p style={{ color: '#dc2626', fontSize: '0.75rem', marginTop: '0.25rem' }}>{errors.confirmPassword}</p>}
            </div>

            <button
              type="submit"
              disabled={loading}
              style={{
                width: '100%',
                backgroundColor: loading ? '#555' : 'black',
                color: '#00FEE5',
                fontWeight: 'bold',
                padding: '0.75rem',
                borderRadius: '0.5rem',
                border: 'none',
                cursor: loading ? 'not-allowed' : 'pointer',
                marginTop: '1.5rem',
                fontFamily: ASSETS.fontFamily,
                fontSize: '1.1rem',
                transition: 'background-color 0.2s'
              }}
            >
              {loading ? 'Inscription...' : "S'inscrire"}
            </button>

            {authError && (
              <p style={{ color: '#dc2626', fontSize: '0.9rem', marginTop: '0.75rem', textAlign: 'center', fontFamily: ASSETS.fontFamily }}>
                ⚠️ {authError}
              </p>
            )}
          </form>

          <div style={{ textAlign: 'center', color: '#374151', marginTop: '1.5rem', fontFamily: ASSETS.fontFamily }}>
            Deja inscrit ? <a href="/login" style={{ color: '#2563eb', fontWeight: '600', textDecoration: 'none' }}>Je me connecte</a>
          </div>
          <div style={{ textAlign: 'center', marginTop: '1rem', display: 'flex', gap: '1rem', justifyContent: 'center' }}>
            <a href="/privacy" style={{ color: '#9ca3af', fontSize: '0.75rem', textDecoration: 'none', fontFamily: ASSETS.fontFamily }}>Politique de confidentialite</a>
            <a href="/terms" style={{ color: '#9ca3af', fontSize: '0.75rem', textDecoration: 'none', fontFamily: ASSETS.fontFamily }}>Conditions d'utilisation</a>
          </div>
        </div>
      </div>
    </div>
  );
}