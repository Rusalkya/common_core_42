-- AlterEnum: ajouter les types de notifications pour les actions de suppression
-- (necessaire pour le module Notification - couvre creation, update ET deletion)
ALTER TYPE "NotificationType" ADD VALUE 'FRIEND_REMOVED';
ALTER TYPE "NotificationType" ADD VALUE 'POST_DELETED';
