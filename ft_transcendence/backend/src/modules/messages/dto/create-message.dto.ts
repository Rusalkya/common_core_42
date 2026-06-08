import { IsString, IsNotEmpty, IsInt, IsOptional, MaxLength } from 'class-validator';
import { ApiProperty, ApiPropertyOptional } from '@nestjs/swagger';

export class CreateMessageDto {
  // Champ backend original
  @ApiPropertyOptional({ description: 'ID du destinataire', example: 2 })
  @IsInt()
  @IsOptional()
  receiverId?: number;

  // Alias frontend : recipientId → receiverId
  @ApiPropertyOptional({ description: 'ID du destinataire (alias)', example: 2 })
  @IsInt()
  @IsOptional()
  recipientId?: number;

  // Champ backend original
  @ApiPropertyOptional({ description: 'Contenu du message', example: 'Salut!' })
  @IsString()
  @IsOptional()
  @MaxLength(1000)
  content?: string;

  // Alias frontend : text → content
  @ApiPropertyOptional({ description: 'Contenu du message (alias)', example: 'Salut!' })
  @IsString()
  @IsOptional()
  @MaxLength(1000)
  text?: string;
}
