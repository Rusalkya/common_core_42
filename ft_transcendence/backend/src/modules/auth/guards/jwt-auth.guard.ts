/**
 * ============================================
 * JWT AUTH GUARD - Protection des routes
 * ============================================
 * 
 * Ce guard protege les routes qui necessitent une authentification.
 * Il utilise la JwtStrategy pour valider le token.
 * 
 * Utilisation :
 *   @UseGuards(JwtAuthGuard)
 *   @Get('profile')
 *   getProfile(@Request() req) {
 *     return req.user;
 *   }
 * 
 * Si le token est absent ou invalide → 401 Unauthorized
 * Si le token est valide → req.user contient l'utilisateur
 * 
 * Responsable: wtohami- (Backend)
 */

import { Injectable, ExecutionContext, UnauthorizedException } from '@nestjs/common';
import { AuthGuard } from '@nestjs/passport';

@Injectable()
export class JwtAuthGuard extends AuthGuard('jwt') {
  /**
   * canActivate() est appele avant chaque requete sur une route protegee.
   * Il delegue la validation a la JwtStrategy via Passport.
   */
  canActivate(context: ExecutionContext) {
    // Appelle la logique de Passport (extraction token → validation → inject user)
    return super.canActivate(context);
  }

  /**
   * handleRequest() est appele apres la validation par Passport.
   * Permet de personnaliser la reponse en cas d'erreur.
   * 
   * @param err - Erreur eventuelle
   * @param user - L'utilisateur retourne par validate() de JwtStrategy
   */
  handleRequest(err: any, user: any) {
    // Si erreur ou pas d'utilisateur → 401
    if (err || !user) {
      throw err || new UnauthorizedException('Token manquant ou invalide. Connectez-vous.');
    }

    // Retourne l'utilisateur → sera injecte dans req.user
    return user;
  }
}
