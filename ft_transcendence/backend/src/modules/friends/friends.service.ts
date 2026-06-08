/**
 * ============================================
 * FRIENDS SERVICE - Systeme d'amis
 * ============================================
 * 
 * Gere les relations d'amitie entre utilisateurs :
 * - Envoyer une demande d'ami
 * - Accepter/Refuser une demande
 * - Supprimer un ami
 * - Lister ses amis
 * - Voir les demandes en attente
 * 
 * Statuts possibles : PENDING, ACCEPTED, REJECTED
 * 
 * Responsable: wtohami- (Backend)
 */

import { Injectable, NotFoundException } from '@nestjs/common';
import { PrismaService } from '../../prisma/prisma.service';
import { ChatGateway } from '../chat/gateways/chat.gateway';
import { NotificationsService } from '../notifications/notifications.service';
import { NotificationType } from '@prisma/client';

@Injectable()
export class FriendsService {
  constructor(
    private readonly prisma: PrismaService,
    private readonly chatGateway: ChatGateway,
    private readonly notificationsService: NotificationsService,
  ) {}

  // Envoyer une demande d'ami
  async sendRequest(senderId: number, receiverId: number) {
    const result = await this.prisma.friend.create({
      data: { senderId, receiverId, status: 'PENDING' },
    });
    // Envoie le toast en temps reel
    this.chatGateway.sendNotification(receiverId, {
      type: 'friend_request',
      message: 'Vous avez recu une demande d\'ami',
    });
    // Sauvegarde en base pour la page notifications
    await this.notificationsService.create(receiverId, senderId, NotificationType.FRIEND_REQUEST);
    return result;
  }

  // Accepter une demande
  async acceptRequest(id: number, userId: number) {
    const request = await this.prisma.friend.findUnique({ where: { id } });
    if (!request || request.receiverId !== userId) {
      throw new NotFoundException('Demande non trouvee');
    }
    const result = await this.prisma.friend.update({
      where: { id },
      data: { status: 'ACCEPTED' },
    });
    // Envoie le toast en temps reel
    this.chatGateway.sendNotification(request.senderId, {
      type: 'friend_accepted',
      message: 'Votre demande d\'ami a ete acceptee',
    });
    // Sauvegarde en base pour la page notifications
    await this.notificationsService.create(request.senderId, userId, NotificationType.FRIEND_ACCEPTED);
    return result;
  }

  // Refuser une demande
  async rejectRequest(id: number, userId: number) {
    const request = await this.prisma.friend.findUnique({ where: { id } });
    if (!request || request.receiverId !== userId) {
      throw new NotFoundException('Demande non trouvee');
    }
    return this.prisma.friend.update({
      where: { id },
      data: { status: 'REJECTED' },
    });
  }

  // Supprimer un ami
  async removeFriend(id: number, userId: number) {
    const friend = await this.prisma.friend.findUnique({ where: { id } });
    if (!friend || (friend.senderId !== userId && friend.receiverId !== userId)) {
      throw new NotFoundException('Ami non trouve');
    }
    // L'autre personne dans la relation
    const otherUserId = friend.senderId === userId ? friend.receiverId : friend.senderId;
    const result = await this.prisma.friend.delete({ where: { id } });
    // Toast temps reel pour l'autre user
    this.chatGateway.sendNotification(otherUserId, {
      type: 'friend_removed',
      message: 'Un de vos amis vous a retire de sa liste',
    });
    // Notification persistante (action de DELETION)
    await this.notificationsService.create(otherUserId, userId, NotificationType.FRIEND_REMOVED);
    return result;
  }

  // Liste des amis d'un utilisateur
  async getFriends(userId: number) {
    return this.prisma.friend.findMany({
      where: {
        status: 'ACCEPTED',
        OR: [{ senderId: userId }, { receiverId: userId }],
      },
      include: {
        sender: { select: { id: true, username: true, avatar: true } },
        receiver: { select: { id: true, username: true, avatar: true } },
      },
    });
  }

  // Demandes en attente recues
  async getPendingRequests(userId: number) {
    return this.prisma.friend.findMany({
      where: { receiverId: userId, status: 'PENDING' },
      include: { sender: { select: { id: true, username: true, avatar: true } } },
    });
  }
}
