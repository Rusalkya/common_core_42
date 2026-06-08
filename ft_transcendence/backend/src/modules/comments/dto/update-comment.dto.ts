import { IsString, IsNotEmpty, MaxLength } from 'class-validator';
import { ApiProperty } from '@nestjs/swagger';

export class UpdateCommentDto {
  @ApiProperty({ description: 'Nouveau contenu', example: 'Commentaire modifie!' })
  @IsString()
  @IsNotEmpty()
  @MaxLength(500)
  content: string;
}
