import { IsString, IsOptional, IsUrl, MinLength, MaxLength } from 'class-validator';
import { ApiPropertyOptional } from '@nestjs/swagger';

// DTO pour modifier un utilisateur (PATCH /users/:id)
// Tous les champs sont optionnels car c'est un PATCH (modification partielle)

export class UpdateUserDto {
  @ApiPropertyOptional({ description: 'Nouveau pseudo', example: 'john_doe' })
  @IsOptional()                    // Champ optionnel
  @IsString()                      // Doit etre une string
  @MinLength(3)                    // Minimum 3 caracteres
  @MaxLength(20)                   // Maximum 20 caracteres
  username?: string;

  @ApiPropertyOptional({ description: 'Nouvelle bio', example: 'Hello, je suis John!' })
  @IsOptional()
  @IsString()
  @MaxLength(200)                  // Bio limitee a 200 caracteres
  bio?: string;

  @ApiPropertyOptional({ description: 'URL de l\'avatar', example: 'https://example.com/avatar.jpg' })
  @IsOptional()
  @IsUrl()                         // Doit etre une URL valide
  avatar?: string;
}