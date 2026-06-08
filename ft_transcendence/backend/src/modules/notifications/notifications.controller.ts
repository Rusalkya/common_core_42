import { Controller, Get, Patch, Param, ParseIntPipe, Request, UseGuards } from '@nestjs/common';
import { ApiTags, ApiOperation, ApiBearerAuth } from '@nestjs/swagger';
import { JwtAuthGuard } from '../auth/guards/jwt-auth.guard';
import { NotificationsService } from './notifications.service';

@ApiTags('notifications')
@Controller('notifications')
export class NotificationsController {
  constructor(private readonly notificationsService: NotificationsService) {}

  // GET /notifications - Mes notifications
  @UseGuards(JwtAuthGuard)
  @Get()
  @ApiBearerAuth('JWT-auth')
  @ApiOperation({ summary: 'Mes notifications' })
  async findAll(@Request() req: any) {
    const userId = req.user.id;
    return this.notificationsService.findByUser(userId);
  }

  // GET /notifications/unread - Nombre de non lues
  @UseGuards(JwtAuthGuard)
  @Get('unread')
  @ApiBearerAuth('JWT-auth')
  @ApiOperation({ summary: 'Nombre de notifications non lues' })
  async getUnreadCount(@Request() req: any) {
    const userId = req.user.id;
    return { count: await this.notificationsService.getUnreadCount(userId) };
  }

  // PATCH /notifications/read-all - Marquer toutes comme lues (doit etre AVANT :id/read)
  @UseGuards(JwtAuthGuard)
  @Patch('read-all')
  @ApiBearerAuth('JWT-auth')
  @ApiOperation({ summary: 'Marquer toutes les notifications comme lues' })
  async markAllAsRead(@Request() req: any) {
    const userId = req.user.id;
    return this.notificationsService.markAllAsRead(userId);
  }

  // PATCH /notifications/:id/read - Marquer comme lue
  @UseGuards(JwtAuthGuard)
  @Patch(':id/read')
  @ApiBearerAuth('JWT-auth')
  @ApiOperation({ summary: 'Marquer une notification comme lue' })
  async markAsRead(@Param('id', ParseIntPipe) id: number, @Request() req: any) {
    const userId = req.user.id;
    return this.notificationsService.markAsRead(id, userId);
  }
}
