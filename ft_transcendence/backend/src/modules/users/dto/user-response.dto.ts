import { ApiProperty } from '@nestjs/swagger';

// DTO de reponse - Ce qu'on renvoie au frontend
// On ne renvoie JAMAIS le mot de passe !

export class UserResponseDto {
  @ApiProperty({ description: 'ID de l\'utilisateur', example: 1 })
  id: number;

  @ApiProperty({ description: 'Email', example: 'john@example.com' })
  email: string;

  @ApiProperty({ description: 'Pseudo', example: 'john_doe' })
  username: string;

  @ApiProperty({ description: 'URL avatar', example: 'https://example.com/avatar.jpg', required: false })
  avatar?: string;

  @ApiProperty({ description: 'Bio', example: 'Hello!', required: false })
  bio?: string;

  @ApiProperty({ description: 'Date de creation' })
  createdAt: Date;
}