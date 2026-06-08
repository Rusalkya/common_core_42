import { Controller, Get, Post, Patch, Param, Body, ParseIntPipe, Request, UseGuards } from '@nestjs/common';
import { ApiTags, ApiOperation, ApiBearerAuth } from '@nestjs/swagger';
import { JwtAuthGuard } from '../auth/guards/jwt-auth.guard';
import { MessagesService } from './messages.service';
import { CreateMessageDto } from './dto/create-message.dto';

@ApiTags('messages')
@Controller('messages')
export class MessagesController {
  constructor(private readonly messagesService: MessagesService) {}

  // GET /messages - Mes conversations
  @UseGuards(JwtAuthGuard)
  @Get()
  @ApiBearerAuth('JWT-auth')
  @ApiOperation({ summary: 'Liste de mes conversations' })
  async getConversations(@Request() req: any) {
    const userId = req.user.id;
    return this.messagesService.getConversations(userId);
  }

  // GET /messages/unread - Nombre de non lus
  @UseGuards(JwtAuthGuard)
  @Get('unread')
  @ApiBearerAuth('JWT-auth')
  @ApiOperation({ summary: 'Nombre de messages non lus' })
  async getUnreadCount(@Request() req: any) {
    const userId = req.user.id;
    return { count: await this.messagesService.getUnreadCount(userId) };
  }

  // GET /messages/conversations - Liste des conversations (doit etre avant :userId)
  @UseGuards(JwtAuthGuard)
  @Get('conversations')
  @ApiBearerAuth('JWT-auth')
  @ApiOperation({ summary: 'Liste de mes conversations' })
  async getConversationsAlias(@Request() req: any) {
    return this.messagesService.getConversations(req.user.id);
  }

  // GET /messages/:userId - Conversation avec un utilisateur
  @UseGuards(JwtAuthGuard)
  @Get(':userId')
  @ApiBearerAuth('JWT-auth')
  @ApiOperation({ summary: 'Conversation avec un utilisateur' })
  async getConversation(@Param('userId', ParseIntPipe) otherUserId: number, @Request() req: any) {
    const userId = req.user.id;
    return this.messagesService.getConversation(userId, otherUserId);
  }

  // POST /messages - Envoyer un message
  @UseGuards(JwtAuthGuard)
  @Post()
  @ApiBearerAuth('JWT-auth')
  @ApiOperation({ summary: 'Envoyer un message' })
  async send(@Request() req: any, @Body() createMessageDto: CreateMessageDto) {
    const senderId = req.user.id;
    // Support alias frontend: recipientId / text
    const receiverId = createMessageDto.receiverId ?? createMessageDto.recipientId;
    const content = createMessageDto.content ?? createMessageDto.text;
    return this.messagesService.send(senderId, receiverId, content);
  }

  // PATCH /messages/:id/read - Marquer comme lu
  @UseGuards(JwtAuthGuard)
  @Patch(':id/read')
  @ApiBearerAuth('JWT-auth')
  @ApiOperation({ summary: 'Marquer un message comme lu' })
  async markAsRead(@Param('id', ParseIntPipe) id: number, @Request() req: any) {
    const userId = req.user.id;
    return this.messagesService.markAsRead(id, userId);
  }
}
