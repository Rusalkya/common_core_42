/**
 * ============================================
 * COMMENTS SERVICE - Gestion des commentaires
 * ============================================
 * 
 * Ce service gere les commentaires sur les posts :
 * - Recuperer les commentaires d'un post
 * - Creer un commentaire
 * - Modifier/Supprimer (auteur seulement)
 * 
 * Responsable: wtohami- (Backend)
 */

import { Injectable, NotFoundException, ForbiddenException } from '@nestjs/common';
import { PrismaService } from '../../prisma/prisma.service';

@Injectable()
export class CommentsService {
  constructor(private readonly prisma: PrismaService) {}

  // Tous les commentaires d'un post
  async findByPost(postId: number) {
    return this.prisma.comment.findMany({
      where: { postId },
      include: { user: { select: { id: true, username: true, avatar: true } } },
      orderBy: { createdAt: 'desc' },
    });
  }

  // Un commentaire par ID
  async findOne(id: number) {
    const comment = await this.prisma.comment.findUnique({
      where: { id },
      include: { user: { select: { id: true, username: true, avatar: true } } },
    });
    if (!comment) {
      throw new NotFoundException(`Commentaire #${id} non trouve`);
    }
    return comment;
  }

  // Creer un commentaire
  async create(userId: number, postId: number, content: string) {
    return this.prisma.comment.create({
      data: { userId, postId, content },
      include: { user: { select: { id: true, username: true, avatar: true } } },
    });
  }

  // Modifier un commentaire (seulement l'auteur)
  async update(id: number, userId: number, content: string) {
    const comment = await this.findOne(id);
    if (comment.userId !== userId) {
      throw new ForbiddenException('Vous ne pouvez modifier que vos commentaires');
    }
    return this.prisma.comment.update({
      where: { id },
      data: { content },
    });
  }

  // Supprimer un commentaire (seulement l'auteur)
  async remove(id: number, userId: number) {
    const comment = await this.findOne(id);
    if (comment.userId !== userId) {
      throw new ForbiddenException('Vous ne pouvez supprimer que vos commentaires');
    }
    return this.prisma.comment.delete({ where: { id } });
  }
}
