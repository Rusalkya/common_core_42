import { Controller, Post, Delete, Param, UseInterceptors, UploadedFile, BadRequestException, UseGuards } from '@nestjs/common';
import { FileInterceptor } from '@nestjs/platform-express';
import type { Multer } from 'multer';
import { ApiTags, ApiOperation, ApiConsumes, ApiBearerAuth } from '@nestjs/swagger';
import { JwtAuthGuard } from '../auth/guards/jwt-auth.guard';
import { UploadService } from './upload.service';

@ApiTags('upload')
@Controller('upload')
export class UploadController {
  constructor(private readonly uploadService: UploadService) {}

  @UseGuards(JwtAuthGuard)
  @Post()
  @ApiBearerAuth('JWT-auth')
  @ApiOperation({ summary: 'Uploader une image' })
  @ApiConsumes('multipart/form-data')
  @UseInterceptors(FileInterceptor('file'))
  async uploadFile(@UploadedFile() file: Express.Multer.File) {
    if (!file) {
      throw new BadRequestException('Aucun fichier fourni');
    }

    // Verifier le type de fichier
    const allowedTypes = ['image/jpeg', 'image/png', 'image/webp', 'image/gif'];
    if (!allowedTypes.includes(file.mimetype)) {
      throw new BadRequestException('Type de fichier non autorise. Utilisez: JPG, PNG, WebP, GIF');
    }

    // Verifier la taille (5MB max)
    const maxSize = 5 * 1024 * 1024;
    if (file.size > maxSize) {
      throw new BadRequestException('Fichier trop volumineux. Maximum: 5MB');
    }

    const url = await this.uploadService.saveFile(file);
    return { url, filename: file.originalname, size: file.size };
  }

  // POST /upload/image - Alias pour le frontend
  @UseGuards(JwtAuthGuard)
  @Post('image')
  @ApiBearerAuth('JWT-auth')
  @ApiOperation({ summary: 'Uploader une image (alias /upload/image)' })
  @ApiConsumes('multipart/form-data')
  @UseInterceptors(FileInterceptor('file'))
  async uploadImage(@UploadedFile() file: Express.Multer.File) {
    return this.uploadFile(file);
  }

  // DELETE /upload/:imageId - Supprimer une image
  @UseGuards(JwtAuthGuard)
  @Delete(':imageId')
  @ApiBearerAuth('JWT-auth')
  @ApiOperation({ summary: 'Supprimer une image' })
  async deleteFile(@Param('imageId') imageId: string) {
    await this.uploadService.deleteFile(imageId);
    return { message: 'Image supprimee' };
  }
}
