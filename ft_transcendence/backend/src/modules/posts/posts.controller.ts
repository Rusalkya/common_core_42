/**
 * ============================================
 * POSTS CONTROLLER - Routes des publications
 * ============================================
 * 
 * Routes disponibles :
 * - GET    /posts          → Liste tous les posts
 * - GET    /posts/:id      → Recupere un post
 * - POST   /posts          → Cree un post (auth requise)
 * - PATCH  /posts/:id      → Modifie un post (auteur only)
 * - DELETE /posts/:id      → Supprime un post (auteur only)
 * - POST   /posts/:id/like → Like un post
 * - DELETE /posts/:id/like → Unlike un post
 * - GET    /posts/user/:id → Posts d'un utilisateur
 * 
 * Responsable: wtohami- (Backend)
 */

import { Controller, Get, Post, Patch, Delete, Param, Body, ParseIntPipe, Request, UseGuards } from '@nestjs/common';
import { ApiTags, ApiOperation, ApiBearerAuth } from '@nestjs/swagger';
import { JwtAuthGuard } from '../auth/guards/jwt-auth.guard';
import { PostsService } from './posts.service';
import { CommentsService } from '../comments/comments.service';
import { ChatGateway } from '../chat/gateways/chat.gateway';
import { NotificationsService } from '../notifications/notifications.service';
import { NotificationType } from '@prisma/client';
import { CreatePostDto } from './dto/create-post.dto';
import { UpdatePostDto } from './dto/update-post.dto';

@ApiTags('posts')
@Controller('posts')
export class PostsController {
  constructor(
    private readonly postsService: PostsService,
    private readonly commentsService: CommentsService,
    private readonly chatGateway: ChatGateway,
    private readonly notificationsService: NotificationsService,
  ) {}

  // GET /posts - Tous les posts
  @Get()
  @ApiOperation({ summary: 'Recuperer tous les posts' })
  async findAll() {
    return this.postsService.findAll();
  }

  // GET /posts/user/:userId - Posts d'un utilisateur (DOIT etre avant :id !)
  @Get('user/:userId')
  @ApiOperation({ summary: 'Posts d\'un utilisateur' })
  async findByUser(@Param('userId', ParseIntPipe) userId: number) {
    return this.postsService.findByUser(userId);
  }

  // GET /posts/:id - Un post
  @Get(':id')
  @ApiOperation({ summary: 'Recuperer un post par ID' })
  async findOne(@Param('id', ParseIntPipe) id: number) {
    return this.postsService.findOne(id);
  }

  // POST /posts - Creer un post (frontend envoie { image, description })
  @UseGuards(JwtAuthGuard)
  @Post()
  @ApiBearerAuth('JWT-auth')
  @ApiOperation({ summary: 'Creer un nouveau post' })
  async create(@Request() req: any, @Body() createPostDto: CreatePostDto) {
    const userId = req.user.id;
    // Support champs frontend (image/description) et champs backend (imageUrl/content)
    const imageUrl = (createPostDto as any).image || createPostDto.imageUrl;
    const content = (createPostDto as any).description || createPostDto.content;
    return this.postsService.create(userId, imageUrl, content);
  }

  // PATCH /posts/:id - Modifier un post (frontend envoie { description })
  @UseGuards(JwtAuthGuard)
  @Patch(':id')
  @ApiBearerAuth('JWT-auth')
  @ApiOperation({ summary: 'Modifier un post' })
  async update(
    @Param('id', ParseIntPipe) id: number,
    @Request() req: any,
    @Body() updatePostDto: UpdatePostDto,
  ) {
    const userId = req.user.id;
    // Support alias description → caption
    const data: any = { ...updatePostDto };
    if ((updatePostDto as any).description !== undefined) {
      data.caption = (updatePostDto as any).description;
    }
    return this.postsService.update(id, userId, data);
  }

  // DELETE /posts/:id - Supprimer un post
  @UseGuards(JwtAuthGuard)
  @Delete(':id')
  @ApiBearerAuth('JWT-auth')
  @ApiOperation({ summary: 'Supprimer un post' })
  async remove(@Param('id', ParseIntPipe) id: number, @Request() req: any) {
    const userId = req.user.id;
    return this.postsService.remove(id, userId);
  }

  // POST /posts/:id/like - Liker un post
  @UseGuards(JwtAuthGuard)
  @Post(':id/like')
  @ApiBearerAuth('JWT-auth')
  @ApiOperation({ summary: 'Liker un post' })
  async like(@Param('id', ParseIntPipe) id: number, @Request() req: any) {
    const userId = req.user.id;
    return this.postsService.like(id, userId);
  }

  // DELETE /posts/:id/like - Unliker un post
  @UseGuards(JwtAuthGuard)
  @Delete(':id/like')
  @ApiBearerAuth('JWT-auth')
  @ApiOperation({ summary: 'Retirer son like' })
  async unlike(@Param('id', ParseIntPipe) id: number, @Request() req: any) {
    const userId = req.user.id;
    return this.postsService.unlike(id, userId);
  }

  // POST /posts/:id/repost - Reposter un post
  @UseGuards(JwtAuthGuard)
  @Post(':id/repost')
  @ApiBearerAuth('JWT-auth')
  @ApiOperation({ summary: 'Reposter un post' })
  async repost(@Param('id', ParseIntPipe) id: number, @Request() req: any) {
    const userId = req.user.id;
    return this.postsService.repost(id, userId);
  }

  // DELETE /posts/:id/repost - Unreposter un post
  @UseGuards(JwtAuthGuard)
  @Delete(':id/repost')
  @ApiBearerAuth('JWT-auth')
  @ApiOperation({ summary: 'Retirer son repost' })
  async unrepost(@Param('id', ParseIntPipe) id: number, @Request() req: any) {
    const userId = req.user.id;
    return this.postsService.unrepost(id, userId);
  }

  // ─── Routes commentaires imbriquees (utilisees par le frontend) ───

  // GET /posts/:postId/comments - Commentaires d'un post
  @Get(':postId/comments')
  @ApiOperation({ summary: 'Commentaires d\'un post' })
  async getComments(@Param('postId', ParseIntPipe) postId: number) {
    return this.commentsService.findByPost(postId);
  }

  // POST /posts/:postId/comments - Creer un commentaire (frontend envoie { text })
  @UseGuards(JwtAuthGuard)
  @Post(':postId/comments')
  @ApiBearerAuth('JWT-auth')
  @ApiOperation({ summary: 'Creer un commentaire sur un post' })
  async createComment(
    @Param('postId', ParseIntPipe) postId: number,
    @Request() req: any,
    @Body() body: { text?: string; content?: string },
  ) {
    const content = body.content ?? body.text;
    const comment = await this.commentsService.create(req.user.id, postId, content);
    const post = await this.postsService.findOne(postId);
    if (post.userId !== req.user.id) {
      // Envoie le toast en temps reel
      this.chatGateway.sendNotification(post.userId, {
        type: 'comment',
        message: 'Quelqu\'un a commente votre dessin',
      });
      // Sauvegarde en base pour la page notifications
      await this.notificationsService.create(post.userId, req.user.id, NotificationType.COMMENT, postId);
    }
    return comment;
  }
}
