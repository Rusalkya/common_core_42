/**
 * @responsable wtohami-
 * @role Tech Lead / Backend
 *
 * USERS MODULE - Gestion des utilisateurs
 *
 * Ce que tu dois faire :
 * - Creer le module, controller et service Users
 * - Endpoints : GET /users, GET /users/:id, PATCH /users/:id, DELETE /users/:id
 * - Implementer la recuperation du profil utilisateur
 * - Gerer la mise a jour du profil (avatar, pseudo, bio)
 * - Implementer la recherche d'utilisateurs
 * - Definir les DTOs dans dto/ (UpdateUserDto, UserResponseDto)
 */
import { Module } from '@nestjs/common';
import { UsersController } from './user.controller';
import { UsersService } from './user.service';
import { UploadModule } from '../upload/upload.module';

@Module({
  imports: [UploadModule],
  controllers: [UsersController],
  providers: [UsersService],
  exports: [UsersService],
})
export class UsersModule {}