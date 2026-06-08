import { Injectable, UnauthorizedException, ConflictException } from '@nestjs/common';
import { JwtService } from '@nestjs/jwt';
import * as bcrypt from 'bcrypt';
import { UsersService } from '../users/user.service';

@Injectable()
export class AuthService {
  private readonly saltRounds: number;

  constructor(
    private readonly usersService: UsersService,
    private readonly jwtService: JwtService,  // Pour generer les tokens JWT
  ) {
    const parsed = Number.parseInt(process.env.BCRYPT_ROUNDS ?? '10', 10);
    this.saltRounds = Number.isNaN(parsed) ? 10 : parsed;
  }

  // ========================================
  // POST /auth/register - Creer un compte
  // ========================================
  async register(email: string, password: string, username: string) {
    const normalizedEmail = email.trim().toLowerCase();
    const normalizedUsername = username.trim();

    const [existingEmail, existingUsername] = await Promise.all([
      this.usersService.findByEmail(normalizedEmail),
      this.usersService.findByUsername(normalizedUsername),
    ]);

    if (existingEmail) {
      throw new ConflictException('Email deja utilise');
    }
    if (existingUsername) {
      throw new ConflictException('Nom d\'utilisateur deja utilise');
    }

    const hashedPassword = await bcrypt.hash(password, this.saltRounds);
    const newUser = await this.usersService.createUser({
      email: normalizedEmail,
      password: hashedPassword,
      username: normalizedUsername,
    });

    return this.generateToken(newUser);
  }


  // ========================================
  // POST /auth/login - Se connecter
  // ========================================
 async login(email: string, password: string) {
  const normalizedEmail = email.trim().toLowerCase();

  // 1. Trouver l'utilisateur par email
  const user = await this.usersService.findByEmail(normalizedEmail);
  if (!user) {
    throw new UnauthorizedException('Identifiants invalides');
  }

  // 2. Verifier le mot de passe
  const isPasswordValid = await bcrypt.compare(password, user.password);
  if (!isPasswordValid) {
    throw new UnauthorizedException('Identifiants invalides');
  }

  // 3. Retourner le token
  return this.generateToken(user);
}

  // ========================================
  // Genere un token JWT
  // ========================================
  private generateToken(user: any) {
    const payload = { sub: user.id, email: user.email };
    return {
      access_token: this.jwtService.sign(payload),
      user: {
        id: user.id,
        email: user.email,
        username: user.username,
      },
    };
  }
}
