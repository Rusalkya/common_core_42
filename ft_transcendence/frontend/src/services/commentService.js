/**
 * @responsable clfouger
 * SERVICE COMMENTAIRES
 */

import api from './api'

export const commentService = {
  create: (postId, text) =>
    api.post(`/posts/${postId}/comments`, { content: text }),

  getByPost: (postId) =>
    api.get(`/posts/${postId}/comments`),

  delete: (commentId) =>
    api.delete(`/comments/${commentId}`),

  update: (commentId, text) =>
    api.patch(`/comments/${commentId}`, { content: text })
}
