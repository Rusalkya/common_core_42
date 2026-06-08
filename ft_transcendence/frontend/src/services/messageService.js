/**
 * @responsable clfouger
 * SERVICE MESSAGES / CHAT
 */

import api from './api'

export const messageService = {
  send: (recipientId, text) =>
    api.post('/messages', { recipientId, text }),

  getHistory: (userId, page = 1, limit = 50) =>
    api.get(`/messages/${userId}`, { params: { page, limit } }),

  getConversations: () =>
    api.get('/messages/conversations')
}
