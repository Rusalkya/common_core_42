/**
 * @responsable clfouger
 * SERVICE UTILISATEURS - Appels API pour les profils
 */

import api from './api'

export const userService = {
  getProfile: (userId) =>
    api.get(`/users/${userId}`),

  getCurrentProfile: () =>
    api.get('/users/me'),

  updateProfile: (data) =>
    api.patch('/users/me', data),

  search: (query) =>
    api.get('/users/search', { params: { q: query } }),

  getAvatar: (userId) =>
    api.get(`/users/${userId}/avatar`, { responseType: 'blob' }),

  uploadAvatar: (file) => {
    const formData = new FormData()
    formData.append('avatar', file)
    return api.post('/users/me/avatar', formData)
  },

  deleteAccount: () =>
    api.delete('/users/me')
}
