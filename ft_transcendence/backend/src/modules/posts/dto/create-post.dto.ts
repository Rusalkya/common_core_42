import { IsString, IsNotEmpty, IsOptional, MaxLength } from 'class-validator';
import { ApiProperty, ApiPropertyOptional } from '@nestjs/swagger';

export class CreatePostDto {
  @ApiProperty({ description: 'URL ou base64 de l\'image' })
  @IsString()
  @IsNotEmpty()
  imageUrl: string;

  @ApiPropertyOptional({ description: 'Contenu/description du post', example: 'Ma super photo!' })
  @IsOptional()
  @IsString()
  @MaxLength(500)
  content?: string;
}
