import React, { useState } from 'react';
import { useNavigate } from 'react-router-dom';
import bg from '../assets/background/background.png';
import logo from '../assets/logo/page_title/logo_gribouillit.png';
import '../styles/globals.css';
import { useAuth } from '../context/AuthContext';

export default function LoginPage() {
  const navigate = useNavigate();
  const { login, error: authError, loading } = useAuth();

  const [formData, setFormData] = useState({ email: '', password: '' });
  const [errors, setErrors] = useState({});
  const FONT = 'Gribouillit2.0, sans-serif';

  const handleChange = (e) => {
    const { name, value } = e.target;
    setFormData(prev => ({ ...prev, [name]: value }));
  };

  const validateForm = () => {
    const e = {};
    if (!formData.email.trim()) e.email = 'Requis';
    if (!formData.password.trim()) e.password = 'Requis';
    return e;
  };

  const handleSubmit = async (e) => {
    e.preventDefault();
    const newErrors = validateForm();
    if (Object.keys(newErrors).length > 0) { setErrors(newErrors); return; }
    const success = await login(formData.email, formData.password);
    if (success) navigate('/home');
  };

  const inputStyle = {
    width: '100%', padding: '0.75rem 1rem',
    border: '2px solid #d1d5db', borderRadius: '0.5rem',
    outline: 'none', color: '#111827',
    fontSize: '1.125rem', fontFamily: FONT, boxSizing: 'border-box'
  };

  return (
    <div style={{
      position: 'fixed', inset: 0, width: '100vw', height: '100vh',
      display: 'flex', alignItems: 'center', justifyContent: 'center',
      backgroundImage: `url(${bg})`, backgroundSize: 'cover',
      backgroundPosition: 'center', overflow: 'hidden', fontFamily: FONT
    }}>
      <div style={{ width: '100%', maxWidth: '650px', zIndex: 10, padding: '1rem' }}>

        <div style={{ textAlign: 'center', marginBottom: '1.5rem' }}>
          <img src={logo} alt="Gribouillit" style={{ maxWidth: '100%', height: 'auto', maxHeight: '280px' }} />
        </div>

        <div style={{
          border: '4px solid black', borderRadius: '8px',
          padding: '2rem', backgroundColor: 'rgba(255,255,255,0.97)', fontFamily: FONT
        }}>
          <h1 style={{ fontSize: '1.875rem', fontWeight: 'bold', textAlign: 'center', marginBottom: '2rem', color: 'black', fontFamily: FONT }}>
            Se connecter
          </h1>

          <form onSubmit={handleSubmit} style={{ display: 'flex', flexDirection: 'column', gap: '1.25rem' }}>

            <div>
              <input type="email" name="email" value={formData.email}
                onChange={handleChange} placeholder="Email" style={inputStyle} />
              {errors.email && <p style={{ color: '#dc2626', fontSize: '0.75rem', marginTop: '0.25rem', fontFamily: FONT }}>{errors.email}</p>}
            </div>

            <div>
              <input type="password" name="password" value={formData.password}
                onChange={handleChange} placeholder="Mot de passe" style={inputStyle} />
              {errors.password && <p style={{ color: '#dc2626', fontSize: '0.75rem', marginTop: '0.25rem', fontFamily: FONT }}>{errors.password}</p>}
            </div>

            <button
              type="submit"
              disabled={loading}
              style={{
                width: '100%', backgroundColor: loading ? '#555' : 'black',
                color: '#00FEE5', fontWeight: 'bold', padding: '0.75rem',
                borderRadius: '0.5rem', border: 'none',
                cursor: loading ? 'not-allowed' : 'pointer',
                marginTop: '0.5rem', fontFamily: FONT, fontSize: '1.1rem'
              }}
            >
              {loading ? 'Connexion...' : 'Se connecter'}
            </button>

            {authError && (
              <p style={{ color: '#dc2626', fontSize: '0.9rem', textAlign: 'center', fontFamily: FONT }}>
                ⚠️ {authError}
              </p>
            )}
          </form>

          <div style={{ textAlign: 'center', color: '#374151', marginTop: '1.5rem', fontFamily: FONT }}>
            Pas de compte ?{' '}
            <a href="/register" style={{ color: '#2563eb', fontWeight: '600', textDecoration: 'none' }}>
              Je m'inscris
            </a>
          </div>
        </div>
      </div>
    </div>
  );
}
