/**
 * @responsable wtohami- (structure) + rgalmich (securite)
 *
 * AUTH MODULE - Gestion de l'authentification
 *
 * wtohami- doit faire :
 * - Creer le module, le controller et le service d'authentification
 * - Implementer les endpoints : POST /auth/login, POST /auth/register, POST /auth/logout
 * - Integrer Passport.js avec les strategies definies par rgalmich
 * - Gerer les sessions et les tokens JWT
 *
 * 
 

 * rgalmich doit faire :
 * - Implementer les strategies Passport (JWT, Local) dans strategies/
 * - Definir les DTOs de validation (login, register) dans dto/
 * - Securiser le hashage des mots de passe (bcrypt)
 * - Mettre en place la protection contre le brute force
 * - Gerer les refresh tokens
 */
import { Module } from '@nestjs/common';
import { JwtModule } from '@nestjs/jwt';
import { PassportModule } from '@nestjs/passport';
import { ConfigService } from '@nestjs/config';
import { AuthController } from './auth.controller';
import { AuthService } from './auth.service';
import { JwtStrategy } from './strategies/jwt.strategy';
import { UsersModule } from '../users/users.module';
import { PrismaModule } from '../../prisma';

@Module({
  imports: [
    // Importe UsersModule pour acceder a UsersService
    UsersModule,

    // Module Passport pour les strategies d'authentification
    PassportModule.register({ defaultStrategy: 'jwt' }),

    // Module Prisma pour l'acces DB dans JwtStrategy
    PrismaModule,

    // Configure le module JWT
    JwtModule.registerAsync({
      inject: [ConfigService],
      useFactory: (configService: ConfigService) => ({
        secret: configService.get<string>('JWT_SECRET'),
        signOptions: { expiresIn: configService.get<string>('JWT_EXPIRES_IN') || '7d' },
      }),
    }),
  ],
  controllers: [AuthController],
  providers: [
    AuthService,
    JwtStrategy,  // Strategie JWT pour valider les tokens
  ],
  exports: [AuthService, JwtStrategy],  // Pour que d'autres modules puissent verifier l'auth
})
export class AuthModule {}