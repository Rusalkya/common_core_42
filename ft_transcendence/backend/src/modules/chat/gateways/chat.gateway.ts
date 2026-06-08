/**
 * ============================================
 * CHAT GATEWAY - WebSocket temps reel
 * ============================================
 * 
 * Gere la communication en temps reel via Socket.io :
 * - Connexion/deconnexion des utilisateurs
 * - Authentification via userId
 * - Rooms de conversation (1-to-1 ou groupes)
 * - Envoi/reception de messages instantanes
 * - Indicateur de frappe (typing)
 * 
 * Evenements WebSocket :
 * - 'authenticate'  → Lie un socket a un userId
 * - 'joinRoom'      → Rejoint une conversation
 * - 'leaveRoom'     → Quitte une conversation
 * - 'sendMessage'   → Envoie un message
 * - 'typing'        → Indique qu'on ecrit
 * - 'userOnline'    → Emis quand un user se connecte
 * - 'userOffline'   → Emis quand un user se deconnecte
 * - 'newMessage'    → Emis quand un message arrive
 * 
 * Responsable: wtohami- (Backend)
 */

import {
  WebSocketGateway,
  WebSocketServer,
  SubscribeMessage,
  OnGatewayConnection,
  OnGatewayDisconnect,
  ConnectedSocket,
  MessageBody,
} from '@nestjs/websockets';
import { Server, Socket } from 'socket.io';
import { PrismaService } from '../../../prisma/prisma.service';

@WebSocketGateway({
  cors: { origin: '*' },
  namespace: '/chat',
})
export class ChatGateway implements OnGatewayConnection, OnGatewayDisconnect {
  @WebSocketServer()
  server: Server;

  // PrismaService est global, pas besoin d'importer PrismaModule explicitement
  constructor(private readonly prisma: PrismaService) {}

  private connectedUsers: Map<string, number> = new Map();

  // Connexion d'un utilisateur
  handleConnection(client: Socket) {
    console.log(`Client connecte: ${client.id}`);
  }

  // Deconnexion d'un utilisateur
  handleDisconnect(client: Socket) {
    const userId = this.connectedUsers.get(client.id);
    if (userId) {
      this.connectedUsers.delete(client.id);
      this.server.emit('userOffline', { userId });
    }
    console.log(`Client deconnecte: ${client.id}`);
  }

  // S'authentifier et rejoindre ses rooms
  @SubscribeMessage('authenticate')
  handleAuthenticate(
    @ConnectedSocket() client: Socket,
    @MessageBody() data: { userId: number },
  ) {
    this.connectedUsers.set(client.id, data.userId);
    client.join(`user_${data.userId}`);
    // Envoie la liste des users actuellement en ligne au nouveau client
    const onlineIds = Array.from(new Set(this.connectedUsers.values()));
    client.emit('onlineUsersList', { userIds: onlineIds });
    // Notifie tout le monde qu'un nouvel user est en ligne
    this.server.emit('userOnline', { userId: data.userId });
    return { success: true };
  }

  // Demander la liste des utilisateurs en ligne
  @SubscribeMessage('getOnlineUsers')
  handleGetOnlineUsers(@ConnectedSocket() client: Socket) {
    const onlineIds = Array.from(new Set(this.connectedUsers.values()));
    client.emit('onlineUsersList', { userIds: onlineIds });
    return { success: true, userIds: onlineIds };
  }

  // Rejoindre une conversation — envoie l'historique si c'est le chat global
  @SubscribeMessage('joinRoom')
  async handleJoinRoom(
    @ConnectedSocket() client: Socket,
    @MessageBody() data: { roomId: string },
  ) {
    client.join(data.roomId);
    if (data.roomId === 'global') {
      // Recupere les 50 derniers messages dans l'ordre chronologique
      const last50 = await this.prisma.globalMessage.findMany({
        orderBy: { createdAt: 'desc' },
        take: 50,
      });
      client.emit('chatHistory', last50.reverse());
    }
    return { success: true, roomId: data.roomId };
  }

  // Quitter une conversation
  @SubscribeMessage('leaveRoom')
  handleLeaveRoom(
    @ConnectedSocket() client: Socket,
    @MessageBody() data: { roomId: string },
  ) {
    client.leave(data.roomId);
    return { success: true };
  }

  // Envoyer un message — sauvegarde en base si c'est le chat global
  @SubscribeMessage('sendMessage')
  async handleSendMessage(
    @ConnectedSocket() client: Socket,
    @MessageBody() data: { roomId: string; content: string; senderId: number; senderUsername?: string },
  ) {
    const timestamp = new Date();
    let dbId: number | undefined;

    if (data.roomId === 'global' && data.senderId) {
      const saved = await this.prisma.globalMessage.create({
        data: {
          content: data.content,
          senderId: data.senderId,
          username: data.senderUsername || String(data.senderId),
          createdAt: timestamp,
        },
      });
      dbId = saved.id;
    }

    this.server.to(data.roomId).emit('newMessage', {
      id: dbId,
      content: data.content,
      senderId: data.senderId,
      senderUsername: data.senderUsername || String(data.senderId),
      timestamp,
    });
    return { success: true };
  }

  // Indicateur "est en train d'ecrire"
  @SubscribeMessage('typing')
  handleTyping(
    @ConnectedSocket() client: Socket,
    @MessageBody() data: { roomId: string; userId: number; isTyping: boolean },
  ) {
    client.to(data.roomId).emit('userTyping', {
      userId: data.userId,
      isTyping: data.isTyping,
    });
  }

  // Envoyer une notification a un utilisateur
  sendNotification(userId: number, notification: any) {
    this.server.to(`user_${userId}`).emit('notification', notification);
  }
}
