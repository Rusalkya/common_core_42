/**
 * ============================================
 * CREATE USER DTO - Validation inscription
 * ============================================
 * 
 * DTO (Data Transfer Object) pour POST /auth/register
 * Definit les champs requis pour creer un compte :
 * - email (obligatoire, format email valide)
 * - password (obligatoire, min 8 caracteres)
 * - username (obligatoire, 3-20 caracteres)
 * - bio (optionnel, max 200 caracteres)
 * - avatar (optionnel, URL valide)
 * 
 * Les decorateurs @Is... valident automatiquement les donnees
 * Les decorateurs @Api... generent la doc Swagger
 * 
 * Responsable: wtohami- (Backend)
 */

import { IsEmail, IsString, IsNotEmpty, MinLength, MaxLength, IsOptional, IsUrl } from 'class-validator';
import { ApiProperty, ApiPropertyOptional } from '@nestjs/swagger';

export class CreateUserDto {
  @ApiProperty({ description: 'Email de l\'utilisateur', example: 'john@example.com' })
  @IsEmail()                       // Doit etre un email valide
  @IsNotEmpty()                    // Obligatoire
  email: string;

  @ApiProperty({ description: 'Mot de passe', example: 'Password123!' })
  @IsString()
  @IsNotEmpty()
  @MinLength(8)                    // Minimum 8 caracteres
  password: string;

  @ApiProperty({ description: 'Pseudo', example: 'john_doe' })
  @IsString()
  @IsNotEmpty()
  @MinLength(3)
  @MaxLength(20)
  username: string;

  @ApiPropertyOptional({ description: 'Bio', example: 'Hello!' })
  @IsOptional()
  @IsString()
  @MaxLength(200)
  bio?: string;

  @ApiPropertyOptional({ description: 'URL avatar' })
  @IsOptional()
  @IsUrl()
  avatar?: string;
}