/**
 * ============================================
 * UPLOAD SERVICE - Gestion des fichiers
 * ============================================
 * 
 * Gere l'upload des images pour les posts et avatars :
 * - Sauvegarde les fichiers dans /uploads
 * - Genere des noms uniques (timestamp)
 * - Retourne l'URL publique du fichier
 * - Permet la suppression de fichiers
 * 
 * Note: Multer gere la validation (taille, type MIME)
 * Config dans le controller avec @UseInterceptors(FileInterceptor)
 * 
 * Responsable: wtohami- (Backend)
 */

import { Injectable } from '@nestjs/common';
import { ConfigService } from '@nestjs/config';
import * as fs from 'fs';
import * as path from 'path';

@Injectable()
export class UploadService {
  private uploadDir: string; // Dossier de destination

  constructor(private configService: ConfigService) {
    this.uploadDir = this.configService.get<string>('UPLOAD_DEST') || './uploads';
    // Creer le dossier s'il n'existe pas
    if (!fs.existsSync(this.uploadDir)) {
      fs.mkdirSync(this.uploadDir, { recursive: true });
    }
  }

  // Sauvegarder un fichier
  async saveFile(file: Express.Multer.File): Promise<string> {
    const filename = `${Date.now()}-${file.originalname}`;
    const filepath = path.join(this.uploadDir, filename);
    fs.writeFileSync(filepath, file.buffer);
    return `/uploads/${filename}`;
  }

  // Supprimer un fichier
  async deleteFile(filename: string): Promise<void> {
    const filepath = path.join(this.uploadDir, filename);
    if (fs.existsSync(filepath)) {
      fs.unlinkSync(filepath);
    }
  }
}
