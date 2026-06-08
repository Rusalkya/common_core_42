/**
 * @responsable clfouger
 * SERVICE AMIS
 */

import api from './api'

export const friendService = {
  request: (userId) =>
    api.post(`/friends/request/${userId}`),

  accept: (requestId) =>
    api.post(`/friends/accept/${requestId}`),

  decline: (requestId) =>
    api.delete(`/friends/decline/${requestId}`),

  remove: (userId) =>
    api.delete(`/friends/${userId}`),

  getAll: () =>
    api.get('/friends'),

  getPending: () =>
    api.get('/friends/requests/pending')
}
