import { Controller, Get, Post, Patch, Delete, Param, Body, ParseIntPipe, Request, UseGuards } from '@nestjs/common';
import { ApiTags, ApiOperation, ApiBearerAuth } from '@nestjs/swagger';
import { JwtAuthGuard } from '../auth/guards/jwt-auth.guard';
import { FriendsService } from './friends.service';

@ApiTags('friends')
@Controller('friends')
export class FriendsController {
  constructor(private readonly friendsService: FriendsService) {}

  // GET /friends - Mes amis
  @UseGuards(JwtAuthGuard)
  @Get()
  @ApiBearerAuth('JWT-auth')
  @ApiOperation({ summary: 'Liste de mes amis' })
  async getFriends(@Request() req: any) {
    return this.friendsService.getFriends(req.user.id);
  }

  // GET /friends/pending - Demandes en attente (alias: /friends/requests/pending)
  @UseGuards(JwtAuthGuard)
  @Get('pending')
  @ApiBearerAuth('JWT-auth')
  @ApiOperation({ summary: 'Demandes d\'amis en attente' })
  async getPendingRequests(@Request() req: any) {
    return this.friendsService.getPendingRequests(req.user.id);
  }

  // GET /friends/requests/pending - Alias frontend
  @UseGuards(JwtAuthGuard)
  @Get('requests/pending')
  @ApiBearerAuth('JWT-auth')
  @ApiOperation({ summary: 'Demandes d\'amis en attente (alias)' })
  async getPendingRequestsAlias(@Request() req: any) {
    return this.friendsService.getPendingRequests(req.user.id);
  }

  // POST /friends/request/:userId - Envoyer une demande
  @UseGuards(JwtAuthGuard)
  @Post('request/:userId')
  @ApiBearerAuth('JWT-auth')
  @ApiOperation({ summary: 'Envoyer une demande d\'ami' })
  async sendRequest(@Param('userId', ParseIntPipe) receiverId: number, @Request() req: any) {
    return this.friendsService.sendRequest(req.user.id, receiverId);
  }

  // POST /friends/accept/:id - Accepter une demande (methode frontend)
  @UseGuards(JwtAuthGuard)
  @Post('accept/:id')
  @ApiBearerAuth('JWT-auth')
  @ApiOperation({ summary: 'Accepter une demande d\'ami (POST)' })
  async acceptRequestPost(@Param('id', ParseIntPipe) id: number, @Request() req: any) {
    return this.friendsService.acceptRequest(id, req.user.id);
  }

  // PATCH /friends/:id/accept - Accepter une demande (methode backend originale)
  @UseGuards(JwtAuthGuard)
  @Patch(':id/accept')
  @ApiBearerAuth('JWT-auth')
  @ApiOperation({ summary: 'Accepter une demande d\'ami (PATCH)' })
  async acceptRequest(@Param('id', ParseIntPipe) id: number, @Request() req: any) {
    return this.friendsService.acceptRequest(id, req.user.id);
  }

  // DELETE /friends/decline/:id - Refuser une demande (methode frontend)
  @UseGuards(JwtAuthGuard)
  @Delete('decline/:id')
  @ApiBearerAuth('JWT-auth')
  @ApiOperation({ summary: 'Refuser une demande d\'ami (DELETE)' })
  async declineRequestDelete(@Param('id', ParseIntPipe) id: number, @Request() req: any) {
    return this.friendsService.rejectRequest(id, req.user.id);
  }

  // PATCH /friends/:id/reject - Refuser une demande (methode backend originale)
  @UseGuards(JwtAuthGuard)
  @Patch(':id/reject')
  @ApiBearerAuth('JWT-auth')
  @ApiOperation({ summary: 'Refuser une demande d\'ami (PATCH)' })
  async rejectRequest(@Param('id', ParseIntPipe) id: number, @Request() req: any) {
    return this.friendsService.rejectRequest(id, req.user.id);
  }

  // DELETE /friends/:id - Supprimer un ami
  @UseGuards(JwtAuthGuard)
  @Delete(':id')
  @ApiBearerAuth('JWT-auth')
  @ApiOperation({ summary: 'Supprimer un ami' })
  async removeFriend(@Param('id', ParseIntPipe) id: number, @Request() req: any) {
    return this.friendsService.removeFriend(id, req.user.id);
  }
}
