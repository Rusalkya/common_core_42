/**
 * @responsable clfouger
 * SERVICE POSTS - Appels API pour les dessins
 */

import api from './api'

export const postService = {
  create: (imageData, description = '') =>
    api.post('/posts', { imageUrl: imageData, content: description }),

  getAll: (page = 1, limit = 20) =>
    api.get('/posts', { params: { page, limit } }),

  getById: (id) =>
    api.get(`/posts/${id}`),

  getByUser: (userId, page = 1) =>
    api.get(`/users/${userId}/posts`, { params: { page } }),

  like: (postId) =>
    api.post(`/posts/${postId}/like`),

  unlike: (postId) =>
    api.delete(`/posts/${postId}/like`),

  repost: (postId) =>
    api.post(`/posts/${postId}/repost`),

  unrepost: (postId) =>
    api.delete(`/posts/${postId}/repost`),

  delete: (postId) =>
    api.delete(`/posts/${postId}`),

  update: (postId, description) =>
    api.patch(`/posts/${postId}`, { description })
}
