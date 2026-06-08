/**
 * @responsable clfouger
 * SERVICE API - Axios configure
 * 
 * Instance centralisee avec interceptors pour gestion des tokens
 */

import axios from 'axios'

const api = axios.create({
  baseURL: import.meta.env.VITE_API_URL,
  headers: {
    'Content-Type': 'application/json'
  }
})

// Ajouter le token JWT a chaque requete
api.interceptors.request.use((config) => {
  const token = localStorage.getItem('token')
  if (token) {
    config.headers.Authorization = `Bearer ${token}`
  }
  return config
}, (error) => {
  return Promise.reject(error)
})

// Gerer les erreurs globales + unwrap {success, data} automatiquement
api.interceptors.response.use(
  (response) => {
    // Le backend wraps tout en { success, data, timestamp }
    // On unwrap pour que res.data soit directement le contenu
    if (response.data && typeof response.data === 'object' && 'success' in response.data && 'data' in response.data) {
      response.data = response.data.data
    }
    return response
  },
  (error) => {
    if (error.response?.status === 401) {
      localStorage.removeItem('token')
      window.location.href = '/login'
    }
    return Promise.reject(error)
  }
)

export default api
