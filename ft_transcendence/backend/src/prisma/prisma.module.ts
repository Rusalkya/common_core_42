import { Global, Module } from '@nestjs/common';
import { PrismaService } from './prisma.service';

@Global() // Rend le module accessible partout sans l'importer
@Module({
  providers: [PrismaService],
  exports: [PrismaService],
})
export class PrismaModule {}
