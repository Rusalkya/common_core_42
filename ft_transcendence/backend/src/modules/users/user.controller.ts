import {
  Controller,
  Get,
  Post,
  Patch,
  Delete,
  Param,
  Body,
  Query,
  ParseIntPipe,
  UseGuards,
  Request,
  UseInterceptors,
  UploadedFile,
  BadRequestException,
} from '@nestjs/common';
import { FileInterceptor } from '@nestjs/platform-express';
import type { Multer } from 'multer';
import { ApiTags, ApiOperation, ApiConsumes, ApiResponse, ApiBearerAuth } from '@nestjs/swagger';
import { JwtAuthGuard } from '../auth/guards/jwt-auth.guard';
import { UsersService } from './user.service';
import { UploadService } from '../upload/upload.service';

@ApiTags('users')
@Controller('users')
export class UsersController {
  constructor(
    private readonly usersService: UsersService,
    private readonly uploadService: UploadService,
  ) {}

  // GET /users - Liste tous les utilisateurs
  @Get()
  @ApiOperation({ summary: 'Recuperer tous les utilisateurs' })
  async findAll() {
    return this.usersService.findAll();
  }

  // GET /users/me - Profil de l'utilisateur connecte
  @UseGuards(JwtAuthGuard)
  @Get('me')
  @ApiBearerAuth('JWT-auth')
  @ApiOperation({ summary: 'Mon profil' })
  async getMe(@Request() req: any) {
    return this.usersService.findOne(req.user.id);
  }

  // GET /users/search?q=xxx - Rechercher des utilisateurs
  @Get('search')
  @ApiOperation({ summary: 'Rechercher des utilisateurs' })
  async search(@Query('q') query: string) {
    return this.usersService.search(query || '');
  }

  // GET /users/:id/posts - Posts d'un utilisateur
  @Get(':id/posts')
  @ApiOperation({ summary: 'Posts d\'un utilisateur' })
  async getPostsByUser(@Param('id', ParseIntPipe) id: number) {
    return this.usersService.getPostsByUser(id);
  }

  // GET /users/:userId/avatar - Avatar d'un utilisateur
  @Get(':userId/avatar')
  @ApiOperation({ summary: 'Avatar d\'un utilisateur' })
  async getAvatar(@Param('userId', ParseIntPipe) userId: number) {
    const user = await this.usersService.findOne(userId);
    return { avatar: user?.avatar ?? null };
  }

  // POST /users/me/avatar - Upload son avatar
  @UseGuards(JwtAuthGuard)
  @Post('me/avatar')
  @ApiBearerAuth('JWT-auth')
  @ApiOperation({ summary: 'Uploader mon avatar' })
  @ApiConsumes('multipart/form-data')
  @UseInterceptors(FileInterceptor('avatar'))
  async uploadAvatar(@UploadedFile() file: Express.Multer.File, @Request() req: any) {
    if (!file) throw new BadRequestException('Aucun fichier fourni');
    const allowedTypes = ['image/jpeg', 'image/png', 'image/webp', 'image/gif'];
    if (!allowedTypes.includes(file.mimetype)) {
      throw new BadRequestException('Type de fichier non autorise. Utilisez: JPG, PNG, WebP, GIF');
    }
    if (file.size > 5 * 1024 * 1024) {
      throw new BadRequestException('Fichier trop volumineux. Maximum: 5MB');
    }
    const url = await this.uploadService.saveFile(file);
    await this.usersService.update(req.user.id, { avatar: url });
    return { url };
  }

  // GET /users/:id - Recupere un utilisateur
  @Get(':id')
  @ApiOperation({ summary: 'Recuperer un utilisateur par ID' })
  async findOne(@Param('id', ParseIntPipe) id: number) {
    return this.usersService.findOne(id);
  }

  // PATCH /users/me - Modifier son propre profil
  @UseGuards(JwtAuthGuard)
  @ApiBearerAuth('JWT-auth')
  @Patch('me')
  @ApiOperation({ summary: 'Modifier mon profil' })
  async updateMe(@Request() req: any, @Body() updateData: any) {
    return this.usersService.update(req.user.id, updateData);
  }

  // PATCH /users/:id - Modifier un utilisateur (admin)
  @UseGuards(JwtAuthGuard)
  @ApiBearerAuth('JWT-auth')
  @Patch(':id')
  @ApiOperation({ summary: 'Modifier un utilisateur' })
  async update(
    @Param('id', ParseIntPipe) id: number,
    @Body() updateData: any,
  ) {
    return this.usersService.update(id, updateData);
  }

  // DELETE /users/me - Supprimer son propre compte
  @UseGuards(JwtAuthGuard)
  @ApiBearerAuth('JWT-auth')
  @Delete('me')
  @ApiOperation({ summary: 'Supprimer mon compte' })
  async removeMe(@Request() req: any) {
    return this.usersService.remove(req.user.id);
  }

  // DELETE /users/:id - Supprime un utilisateur
  @UseGuards(JwtAuthGuard)
  @ApiBearerAuth('JWT-auth')
  @Delete(':id')
  @ApiOperation({ summary: 'Supprimer un utilisateur' })
  async remove(@Param('id', ParseIntPipe) id: number) {
    return this.usersService.remove(id);
  }
}