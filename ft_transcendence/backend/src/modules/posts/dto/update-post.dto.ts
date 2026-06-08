import { IsString, IsOptional, MaxLength } from 'class-validator';
import { ApiPropertyOptional } from '@nestjs/swagger';

export class UpdatePostDto {
  @ApiPropertyOptional({ description: 'Nouvelle legende', example: 'Legende modifiee!' })
  @IsOptional()
  @IsString()
  @MaxLength(500)
  caption?: string;
}
