/**
 * ============================================
 * PUBLIC API CONTROLLER - Endpoints proteges par cle API
 * ============================================
 *
 * Expose une API publique en lecture seule pour scripts/integrations
 * tierces. Protegee par cle API (header `x-api-key`) - SEPAREE du JWT.
 *
 * Endpoints disponibles :
 * - GET    /api/public/stats       : statistiques globales
 * - GET    /api/public/users       : liste publique des utilisateurs
 * - GET    /api/public/users/:id   : profil public d'un utilisateur
 * - GET    /api/public/posts       : liste des dessins publies
 * - POST   /api/public/echo        : test simple (renvoie le payload)
 * - PUT    /api/public/echo/:id    : test simple PUT
 * - DELETE /api/public/echo/:id    : test simple DELETE
 *
 * Module "Public API" du sujet ft_transcendence :
 *   secured API key + rate limiting + documentation + 5+ endpoints
 */

import {
  Body,
  Controller,
  Delete,
  Get,
  Param,
  ParseIntPipe,
  Post,
  Put,
  Query,
  UseGuards,
} from '@nestjs/common';
import {
  ApiOkResponse,
  ApiOperation,
  ApiSecurity,
  ApiTags,
} from '@nestjs/swagger';
import { PrismaService } from '../../prisma/prisma.service';
import { ApiKeyGuard } from './api-key.guard';

@ApiTags('public-api')
@ApiSecurity('api-key')
@UseGuards(ApiKeyGuard)
@Controller('public')
export class PublicApiController {
  constructor(private readonly prisma: PrismaService) {}

  @Get('stats')
  @ApiOperation({ summary: 'Statistiques globales de la plateforme' })
  @ApiOkResponse({ description: 'Compteurs users / posts / comments' })
  async getStats() {
    const [users, posts, comments] = await Promise.all([
      this.prisma.user.count(),
      this.prisma.post.count(),
      this.prisma.comment.count(),
    ]);
    return { users, posts, comments };
  }

  @Get('users')
  @ApiOperation({ summary: 'Liste publique des utilisateurs' })
  async listUsers(@Query('limit') limit?: string) {
    const take = Math.min(Number(limit) || 20, 100);
    return this.prisma.user.findMany({
      take,
      select: {
        id: true,
        username: true,
        avatar: true,
        bio: true,
        createdAt: true,
      },
      orderBy: { createdAt: 'desc' },
    });
  }

  @Get('users/:id')
  @ApiOperation({ summary: "Profil public d'un utilisateur" })
  async getUser(@Param('id', ParseIntPipe) id: number) {
    return this.prisma.user.findUnique({
      where: { id },
      select: {
        id: true,
        username: true,
        avatar: true,
        bio: true,
        createdAt: true,
      },
    });
  }

  @Get('posts')
  @ApiOperation({ summary: 'Liste des dessins publies' })
  async listPosts(@Query('limit') limit?: string) {
    const take = Math.min(Number(limit) || 20, 100);
    return this.prisma.post.findMany({
      take,
      orderBy: { createdAt: 'desc' },
      include: {
        user: { select: { id: true, username: true, avatar: true } },
      },
    });
  }

  @Post('echo')
  @ApiOperation({ summary: 'POST de test (renvoie le payload)' })
  echoPost(@Body() body: any) {
    return { received: body, at: new Date().toISOString() };
  }

  @Put('echo/:id')
  @ApiOperation({ summary: 'PUT de test (renvoie id + payload)' })
  echoPut(@Param('id') id: string, @Body() body: any) {
    return { id, body, method: 'PUT', at: new Date().toISOString() };
  }

  @Delete('echo/:id')
  @ApiOperation({ summary: 'DELETE de test' })
  echoDelete(@Param('id') id: string) {
    return { id, deleted: true, at: new Date().toISOString() };
  }
}
