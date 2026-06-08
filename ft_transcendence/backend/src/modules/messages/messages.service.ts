/**
 * ============================================
 * MESSAGES SERVICE - Messagerie privee
 * ============================================
 * 
 * Gere la messagerie entre utilisateurs :
 * - Envoyer un message
 * - Recuperer une conversation
 * - Lister toutes les conversations
 * - Marquer comme lu
 * - Compter les messages non lus
 * 
 * Note: Le temps reel est gere par ChatGateway (WebSocket)
 * 
 * Responsable: wtohami- (Backend)
 */

import { Injectable, NotFoundException } from '@nestjs/common';
import { PrismaService } from '../../prisma/prisma.service';
import { ChatGateway } from '../chat/gateways/chat.gateway';

@Injectable()
export class MessagesService {
  constructor(
    private readonly prisma: PrismaService,
    private readonly chatGateway: ChatGateway,
  ) {}

  // Envoyer un message
  async send(senderId: number, receiverId: number, content: string) {
    const message = await this.prisma.message.create({
      data: { senderId, receiverId, content, read: false },
      include: {
        sender: { select: { id: true, username: true, avatar: true } },
      },
    });
    // Notifier le destinataire en temps reel
    this.chatGateway.server.to(`user_${receiverId}`).emit('newPrivateMessage', {
      id: message.id,
      content: message.content,
      senderId: message.senderId,
      receiverId: message.receiverId,
      createdAt: message.createdAt,
      sender: message.sender,
    });
    return message;
  }

  // Conversation entre deux utilisateurs
  async getConversation(userId: number, otherUserId: number) {
    return this.prisma.message.findMany({
      where: {
        OR: [
          { senderId: userId, receiverId: otherUserId },
          { senderId: otherUserId, receiverId: userId },
        ],
      },
      orderBy: { createdAt: 'asc' },
    });
  }

  // Liste des conversations (derniers messages)
  async getConversations(userId: number) {
    const messages = await this.prisma.message.findMany({
      where: { OR: [{ senderId: userId }, { receiverId: userId }] },
      include: {
        sender: { select: { id: true, username: true, avatar: true } },
        receiver: { select: { id: true, username: true, avatar: true } },
      },
      orderBy: { createdAt: 'desc' },
    });
    // Grouper par conversation (simplifie)
    return messages;
  }

  // Marquer comme lu
  async markAsRead(messageId: number, userId: number) {
    const message = await this.prisma.message.findUnique({ where: { id: messageId } });
    if (!message || message.receiverId !== userId) {
      throw new NotFoundException('Message non trouve');
    }
    return this.prisma.message.update({
      where: { id: messageId },
      data: { read: true },
    });
  }

  // Messages non lus
  async getUnreadCount(userId: number) {
    return this.prisma.message.count({
      where: { receiverId: userId, read: false },
    });
  }
}
