/**
 * ============================================
 * POSTS SERVICE - Gestion des publications
 * ============================================
 * 
 * Ce service gere toute la logique metier des posts :
 * - CRUD (Create, Read, Update, Delete)
 * - Systeme de likes
 * - Recuperation des posts par utilisateur
 * 
 * Responsable: wtohami- (Backend)
 */

import { Injectable, NotFoundException, ForbiddenException } from '@nestjs/common';
import { PrismaService } from '../../prisma/prisma.service';
import { ChatGateway } from '../chat/gateways/chat.gateway';
import { NotificationsService } from '../notifications/notifications.service';
import { NotificationType } from '@prisma/client';

@Injectable()
export class PostsService {
  constructor(
    private readonly prisma: PrismaService,
    private readonly chatGateway: ChatGateway,
    private readonly notificationsService: NotificationsService,
  ) {}

  // Recuperer tous les posts avec l'auteur et le nombre de likes
  async findAll() {
    return this.prisma.post.findMany({
      include: {
        user: { select: { id: true, username: true, avatar: true } },
        likes: true,
        _count: { select: { comments: true, likes: true, reposts: true } },
      },
      orderBy: { createdAt: 'desc' },
    });
  }

  // Recuperer un post par ID
  async findOne(id: number) {
    const post = await this.prisma.post.findUnique({
      where: { id },
      include: {
        user: { select: { id: true, username: true, avatar: true } },
        comments: {
          include: { user: { select: { id: true, username: true, avatar: true } } },
          orderBy: { createdAt: 'desc' },
        },
        likes: true,
        _count: { select: { comments: true, likes: true, reposts: true } },
      },
    });
    if (!post) {
      throw new NotFoundException(`Post #${id} non trouve`);
    }
    return post;
  }

  // Creer un post
  async create(userId: number, imageUrl: string, caption?: string) {
    return this.prisma.post.create({
      data: { userId, imageUrl, caption },
      include: { user: { select: { id: true, username: true, avatar: true } } },
    });
  }

  // Modifier un post (seulement l'auteur)
  async update(id: number, userId: number, updateData: { caption?: string }) {
    const post = await this.findOne(id);
    if (post.userId !== userId) {
      throw new ForbiddenException('Vous ne pouvez modifier que vos propres posts');
    }
    return this.prisma.post.update({
      where: { id },
      data: updateData,
    });
  }

  // Supprimer un post (seulement l'auteur)
  async remove(id: number, userId: number) {
    const post = await this.findOne(id);
    if (post.userId !== userId) {
      throw new ForbiddenException('Vous ne pouvez supprimer que vos propres posts');
    }
    return this.prisma.post.delete({ where: { id } });
  }

  // Liker un post
  async like(postId: number, userId: number) {
    const post = await this.findOne(postId);
    const result = await this.prisma.like.upsert({
      where: { userId_postId: { postId, userId } },
      create: { postId, userId },
      update: {},
    });
    if (post.userId !== userId) {
      // Envoie le toast en temps reel
      this.chatGateway.sendNotification(post.userId, {
        type: 'like',
        message: 'Quelqu\'un a aime votre dessin',
      });
      // Sauvegarde en base pour la page notifications
      await this.notificationsService.create(post.userId, userId, NotificationType.LIKE, postId);
    }
    return result;
  }

  // Unliker un post
  async unlike(postId: number, userId: number) {
    return this.prisma.like.delete({
      where: { userId_postId: { postId, userId } },
    });
  }

  // Reposter un post
  async repost(postId: number, userId: number) {
    const post = await this.findOne(postId);
    const result = await this.prisma.repost.upsert({
      where: { userId_postId: { postId, userId } },
      create: { postId, userId },
      update: {},
    });
    if (post.userId !== userId) {
      // Envoie le toast en temps reel
      this.chatGateway.sendNotification(post.userId, {
        type: 'repost',
        message: 'Quelqu\'un a republie votre dessin',
      });
      // Sauvegarde en base pour la page notifications
      await this.notificationsService.create(post.userId, userId, NotificationType.REPOST, postId);
    }
    return result;
  }

  // Unreposter un post
  async unrepost(postId: number, userId: number) {
    return this.prisma.repost.delete({
      where: { userId_postId: { postId, userId } },
    });
  }

  // Posts d'un utilisateur specifique
  async findByUser(userId: number) {
    return this.prisma.post.findMany({
      where: { userId },
      include: { _count: { select: { comments: true, likes: true, reposts: true } } },
      orderBy: { createdAt: 'desc' },
    });
  }
}