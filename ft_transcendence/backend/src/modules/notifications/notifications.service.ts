/**
 * ============================================
 * NOTIFICATIONS SERVICE - Alertes utilisateur
 * ============================================
 * 
 * Gere les notifications pour informer les users :
 * - Nouveau like sur un post
 * - Nouveau commentaire
 * - Demande d'ami recue
 * - Demande d'ami acceptee
 * - Nouveau message
 * 
 * Types: LIKE, COMMENT, FRIEND_REQUEST, FRIEND_ACCEPTED, MESSAGE
 * 
 * Responsable: wtohami- (Backend)
 */

import { Injectable } from '@nestjs/common';
import { PrismaService } from '../../prisma/prisma.service';
import { NotificationType } from '@prisma/client';

@Injectable()
export class NotificationsService {
  constructor(private readonly prisma: PrismaService) {}

  // Creer une notification
  async create(userId: number, fromUserId: number, type: NotificationType, postId?: number) {
    return this.prisma.notification.create({
      data: { userId, fromUserId, type, postId, read: false },
    });
  }

  // Notifications d'un utilisateur
  async findByUser(userId: number) {
    return this.prisma.notification.findMany({
      where: { userId },
      include: { fromUser: { select: { id: true, username: true, avatar: true } } },
      orderBy: { createdAt: 'desc' },
    });
  }

  // Marquer comme lue
  async markAsRead(id: number, userId: number) {
    return this.prisma.notification.updateMany({
      where: { id, userId },
      data: { read: true },
    });
  }

  // Marquer toutes comme lues
  async markAllAsRead(userId: number) {
    return this.prisma.notification.updateMany({
      where: { userId, read: false },
      data: { read: true },
    });
  }

  // Nombre de non lues
  async getUnreadCount(userId: number) {
    return this.prisma.notification.count({
      where: { userId, read: false },
    });
  }
}
