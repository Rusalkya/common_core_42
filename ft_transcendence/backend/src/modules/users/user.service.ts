import { Injectable, NotFoundException } from '@nestjs/common';
import { PrismaService } from '../../prisma/prisma.service';

// Champs a exclure du retour (jamais envoyer le mot de passe au client)
const USER_SELECT = {
  id: true,
  email: true,
  username: true,
  avatar: true,
  bio: true,
  createdAt: true,
  updatedAt: true,
};

@Injectable()
export class UsersService {
  constructor(private readonly prisma: PrismaService) {}

  // GET /users - Recuperer tous les utilisateurs (sans mot de passe)
  async findAll() {
    return this.prisma.user.findMany({ select: USER_SELECT });
  }

  // GET /users/:id - Recuperer un utilisateur par ID (sans mot de passe)
  async findOne(id: number) {
    const user = await this.prisma.user.findUnique({
      where: { id },
      select: USER_SELECT,
    });
    if (!user) {
      throw new NotFoundException(`User #${id} not found`);
    }
    return user;
  }

  // GET /users/email/:email - Trouver par email (auth — retourne le mot de passe hache)
  async findByEmail(email: string) {
    return this.prisma.user.findUnique({ where: { email } });
  }

  // GET /users/search?q=xxx - Chercher par username ou email
  async search(query: string) {
    return this.prisma.user.findMany({
      where: {
        OR: [
          { username: { contains: query, mode: 'insensitive' } },
          { email: { contains: query, mode: 'insensitive' } },
        ],
      },
      select: USER_SELECT,
    });
  }

  // GET /users/:id/posts - Posts d'un utilisateur
  async getPostsByUser(userId: number) {
    await this.findOne(userId); // throw si inexistant
    return this.prisma.post.findMany({
      where: { userId },
      include: { _count: { select: { comments: true, likes: true } } },
      orderBy: { createdAt: 'desc' },
    });
  }

  // Trouver par username (auth)
  async findByUsername(username: string) {
    return this.prisma.user.findUnique({ where: { username } });
  }

  // Creer un utilisateur (auth)
  async createUser(data: { email: string; password: string; username: string }) {
    return this.prisma.user.create({ data, select: { ...USER_SELECT, password: false } });
  }

  // PATCH /users/:id - Modifier un utilisateur
  async update(id: number, updateData: any) {
    await this.findOne(id);
    // Empecher de changer email/password directement par cette route
    const { password, ...safeData } = updateData;
    return this.prisma.user.update({
      where: { id },
      data: safeData,
      select: USER_SELECT,
    });
  }

  // DELETE /users/:id - Supprimer un utilisateur
  async remove(id: number) {
    await this.findOne(id);
    return this.prisma.user.delete({ where: { id } });
  }
}