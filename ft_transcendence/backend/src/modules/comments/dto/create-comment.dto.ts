import { IsString, IsNotEmpty, IsInt, MaxLength } from 'class-validator';
import { ApiProperty } from '@nestjs/swagger';

export class CreateCommentDto {
  @ApiProperty({ description: 'ID du post', example: 1 })
  @IsInt()
  @IsNotEmpty()
  postId: number;

  @ApiProperty({ description: 'Contenu du commentaire', example: 'Super dessin!' })
  @IsString()
  @IsNotEmpty()
  @MaxLength(500)
  content: string;
}
