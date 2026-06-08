import { Controller, Post, Body, Get, UseGuards, Request } from '@nestjs/common';
import { ApiTags, ApiOperation, ApiBearerAuth } from '@nestjs/swagger';
import { Throttle } from '@nestjs/throttler';
import { AuthService } from './auth.service';
import { JwtAuthGuard } from './guards/jwt-auth.guard';
import { CreateUserDto } from '../users/dto/create-user.dto';
import { LoginDto } from './dto/login.dto';
import { SanitizePipe } from '../../common/pipes';

@ApiTags('auth')
@Controller('auth')
export class AuthController {
  constructor(private readonly authService: AuthService) {}

  // ========================================
  // POST /auth/register - Creer un compte
  // ========================================
  @Throttle({ auth: { limit: process.env.NODE_ENV === 'production' ? 3 : 50, ttl: 60000 } })
  @Post('register')
  @ApiOperation({ summary: 'Creer un nouveau compte' })
    async register(@Body(SanitizePipe) createUserDto: CreateUserDto) {
        const { email, password, username } = createUserDto;
        return this.authService.register(email, password, username);
}

  // ========================================
  // POST /auth/login - Se connecter
  // ========================================
  @Throttle({ auth: { limit: process.env.NODE_ENV === 'production' ? 5 : 50, ttl: 60000 } })
  @Post('login')
  @ApiOperation({ summary: 'Se connecter' })
  async login(@Body(SanitizePipe) loginDto: LoginDto) {
        const { email, password } = loginDto;
        return this.authService.login(email, password);
    }

  // ========================================
  // GET /auth/me - Recuperer le profil connecte
  // ========================================
  @UseGuards(JwtAuthGuard)     // Protege la route : token JWT obligatoire
  @ApiBearerAuth('JWT-auth')   // Affiche le cadenas dans Swagger
  @Get('me')
  @ApiOperation({ summary: 'Recuperer mon profil' })
  async getMe(@Request() req: any) {
        return req.user;
    }
}
