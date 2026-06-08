import { Controller, Get, Post, Patch, Delete, Param, Body, ParseIntPipe, Request, UseGuards } from '@nestjs/common';
import { ApiTags, ApiOperation, ApiBearerAuth } from '@nestjs/swagger';
import { JwtAuthGuard } from '../auth/guards/jwt-auth.guard';
import { CommentsService } from './comments.service';
import { CreateCommentDto } from './dto/create-comment.dto';
import { UpdateCommentDto } from './dto/update-comment.dto';

@ApiTags('comments')
@Controller('comments')
export class CommentsController {
  constructor(private readonly commentsService: CommentsService) {}

  // GET /comments/post/:postId - Commentaires d'un post
  @Get('post/:postId')
  @ApiOperation({ summary: 'Commentaires d\'un post' })
  async findByPost(@Param('postId', ParseIntPipe) postId: number) {
    return this.commentsService.findByPost(postId);
  }

  // POST /comments - Creer un commentaire
  @UseGuards(JwtAuthGuard)
  @Post()
  @ApiBearerAuth('JWT-auth')
  @ApiOperation({ summary: 'Creer un commentaire' })
  async create(@Request() req: any, @Body() createCommentDto: CreateCommentDto) {
    const userId = req.user.id;
    const { postId, content } = createCommentDto;
    return this.commentsService.create(userId, postId, content);
  }

  // PATCH /comments/:id - Modifier un commentaire
  @UseGuards(JwtAuthGuard)
  @Patch(':id')
  @ApiBearerAuth('JWT-auth')
  @ApiOperation({ summary: 'Modifier un commentaire' })
  async update(
    @Param('id', ParseIntPipe) id: number,
    @Request() req: any,
    @Body() updateCommentDto: UpdateCommentDto,
  ) {
    const userId = req.user.id;
    // Support alias frontend: text → content
    const content = updateCommentDto.content ?? (updateCommentDto as any).text;
    return this.commentsService.update(id, userId, content);
  }

  // DELETE /comments/:id - Supprimer un commentaire
  @UseGuards(JwtAuthGuard)
  @Delete(':id')
  @ApiBearerAuth('JWT-auth')
  @ApiOperation({ summary: 'Supprimer un commentaire' })
  async remove(@Param('id', ParseIntPipe) id: number, @Request() req: any) {
    const userId = req.user.id;
    return this.commentsService.remove(id, userId);
  }
}
