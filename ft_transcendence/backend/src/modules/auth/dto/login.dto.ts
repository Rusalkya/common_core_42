/**
 * ============================================
 * LOGIN DTO - Validation connexion
 * ============================================
 * 
 * DTO pour POST /auth/login
 * Valide les identifiants de connexion :
 * - email (obligatoire, format email)
 * - password (obligatoire, min 8 caracteres)
 * 
 * Responsable: wtohami- (Backend)
 */

import { IsEmail, IsString, IsNotEmpty, MinLength } from 'class-validator';
import { ApiProperty } from '@nestjs/swagger';

export class LoginDto {
  @ApiProperty({ description: 'Email', example: 'john@example.com' })
  @IsEmail()
  @IsNotEmpty()
  email: string;

  @ApiProperty({ description: 'Mot de passe', example: 'Password123!' })
  @IsString()
  @IsNotEmpty()
  @MinLength(8)
  password: string;
}