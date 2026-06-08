/**
 * ============================================
 * JWT STRATEGY - Strategie d'authentification JWT
 * ============================================
 * 
 * Cette strategie est utilisee par Passport.js pour valider
 * les tokens JWT envoyes dans le header Authorization.
 * 
 * Fonctionnement :
 * 1. Le client envoie une requete avec le header : Authorization: Bearer <token>
 * 2. Passport extrait le token du header
 * 3. Le token est verifie avec le JWT_SECRET
 * 4. Si valide, le payload (sub, email) est extrait
 * 5. validate() est appele → on recupere le user en DB
 * 6. Le user est injecte dans req.user pour le controller
 * 
 * Utilisation dans un controller :
 *   @UseGuards(JwtAuthGuard)
 *   @Get('profile')
 *   getProfile(@Request() req) {
 *     return req.user; // ← Le user est dispo ici grace a validate()
 *   }
 * 
 * Responsable: wtohami- (Backend)
 */

import { Injectable, UnauthorizedException } from '@nestjs/common';
import { PassportStrategy } from '@nestjs/passport';
import { ExtractJwt, Strategy } from 'passport-jwt';
import { ConfigService } from '@nestjs/config';
import { PrismaService } from '../../../prisma/prisma.service';

// Le payload contenu dans le token JWT (defini dans auth.service.ts → generateToken)
interface JwtPayload {
  sub: number;    // L'ID de l'utilisateur
  email: string;  // L'email de l'utilisateur
}

@Injectable()
export class JwtStrategy extends PassportStrategy(Strategy) {
  constructor(
    private readonly configService: ConfigService,
    private readonly prisma: PrismaService,
  ) {
    // Configuration de la strategie JWT
    super({
      // Ou trouver le token : dans le header Authorization: Bearer <token>
      jwtFromRequest: ExtractJwt.fromAuthHeaderAsBearerToken(),

      // Ne pas accepter les tokens expires
      ignoreExpiration: false,

      // Cle secrete pour verifier la signature du token
      secretOrKey: configService.get<string>('JWT_SECRET'),
    });
  }

  /**
   * validate() est appele automatiquement par Passport apres verification du token.
   * Le retour de cette fonction est injecte dans req.user.
   * 
   * @param payload - Le contenu decode du token JWT { sub: userId, email }
   * @returns L'utilisateur trouve en base de donnees (sans le mot de passe)
   */
  async validate(payload: JwtPayload) {
    // On cherche l'utilisateur en DB avec l'ID du token
    const user = await this.prisma.user.findUnique({
      where: { id: payload.sub },
      select: {
        id: true,
        email: true,
        username: true,
        avatar: true,
        bio: true,
        createdAt: true,
        // On ne selectionne PAS le password pour la securite
      },
    });

    // Si l'utilisateur n'existe plus en DB (supprime entre-temps)
    if (!user) {
      throw new UnauthorizedException('Utilisateur non trouve ou token invalide');
    }

    // Ce retour sera disponible dans req.user dans les controllers
    return user;
  }
}
