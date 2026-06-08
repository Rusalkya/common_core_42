DO $$
BEGIN
	CREATE TYPE "FriendStatus" AS ENUM ('PENDING', 'ACCEPTED', 'REJECTED');
EXCEPTION
	WHEN duplicate_object THEN NULL;
END $$;

DO $$
BEGIN
	CREATE TYPE "NotificationType" AS ENUM ('LIKE', 'COMMENT', 'FRIEND_REQUEST', 'FRIEND_ACCEPTED', 'MESSAGE');
EXCEPTION
	WHEN duplicate_object THEN NULL;
END $$;

CREATE TABLE IF NOT EXISTS "User" (
	"id" SERIAL PRIMARY KEY,
	"email" TEXT NOT NULL UNIQUE,
	"password" TEXT NOT NULL,
	"username" TEXT NOT NULL UNIQUE,
	"avatar" TEXT,
	"bio" TEXT,
	"createdAt" TIMESTAMP(3) NOT NULL DEFAULT CURRENT_TIMESTAMP,
	"updatedAt" TIMESTAMP(3) NOT NULL DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE IF NOT EXISTS "Post" (
	"id" SERIAL PRIMARY KEY,
	"imageUrl" TEXT NOT NULL,
	"caption" TEXT,
	"userId" INTEGER NOT NULL,
	"createdAt" TIMESTAMP(3) NOT NULL DEFAULT CURRENT_TIMESTAMP,
	"updatedAt" TIMESTAMP(3) NOT NULL DEFAULT CURRENT_TIMESTAMP,
	CONSTRAINT "Post_userId_fkey" FOREIGN KEY ("userId") REFERENCES "User"("id") ON DELETE CASCADE ON UPDATE CASCADE
);

CREATE TABLE IF NOT EXISTS "Comment" (
	"id" SERIAL PRIMARY KEY,
	"content" TEXT NOT NULL,
	"userId" INTEGER NOT NULL,
	"postId" INTEGER NOT NULL,
	"createdAt" TIMESTAMP(3) NOT NULL DEFAULT CURRENT_TIMESTAMP,
	"updatedAt" TIMESTAMP(3) NOT NULL DEFAULT CURRENT_TIMESTAMP,
	CONSTRAINT "Comment_userId_fkey" FOREIGN KEY ("userId") REFERENCES "User"("id") ON DELETE CASCADE ON UPDATE CASCADE,
	CONSTRAINT "Comment_postId_fkey" FOREIGN KEY ("postId") REFERENCES "Post"("id") ON DELETE CASCADE ON UPDATE CASCADE
);

CREATE TABLE IF NOT EXISTS "Like" (
	"userId" INTEGER NOT NULL,
	"postId" INTEGER NOT NULL,
	"createdAt" TIMESTAMP(3) NOT NULL DEFAULT CURRENT_TIMESTAMP,
	CONSTRAINT "Like_pkey" PRIMARY KEY ("userId", "postId"),
	CONSTRAINT "Like_userId_fkey" FOREIGN KEY ("userId") REFERENCES "User"("id") ON DELETE CASCADE ON UPDATE CASCADE,
	CONSTRAINT "Like_postId_fkey" FOREIGN KEY ("postId") REFERENCES "Post"("id") ON DELETE CASCADE ON UPDATE CASCADE
);

CREATE TABLE IF NOT EXISTS "Friend" (
	"id" SERIAL PRIMARY KEY,
	"senderId" INTEGER NOT NULL,
	"receiverId" INTEGER NOT NULL,
	"status" "FriendStatus" NOT NULL DEFAULT 'PENDING',
	"createdAt" TIMESTAMP(3) NOT NULL DEFAULT CURRENT_TIMESTAMP,
	"updatedAt" TIMESTAMP(3) NOT NULL DEFAULT CURRENT_TIMESTAMP,
	CONSTRAINT "Friend_senderId_fkey" FOREIGN KEY ("senderId") REFERENCES "User"("id") ON DELETE CASCADE ON UPDATE CASCADE,
	CONSTRAINT "Friend_receiverId_fkey" FOREIGN KEY ("receiverId") REFERENCES "User"("id") ON DELETE CASCADE ON UPDATE CASCADE,
	CONSTRAINT "Friend_sender_receiver_unique" UNIQUE ("senderId", "receiverId"),
	CONSTRAINT "Friend_not_self" CHECK ("senderId" <> "receiverId")
);

CREATE TABLE IF NOT EXISTS "Message" (
	"id" SERIAL PRIMARY KEY,
	"content" TEXT NOT NULL,
	"senderId" INTEGER NOT NULL,
	"receiverId" INTEGER NOT NULL,
	"read" BOOLEAN NOT NULL DEFAULT false,
	"createdAt" TIMESTAMP(3) NOT NULL DEFAULT CURRENT_TIMESTAMP,
	CONSTRAINT "Message_senderId_fkey" FOREIGN KEY ("senderId") REFERENCES "User"("id") ON DELETE CASCADE ON UPDATE CASCADE,
	CONSTRAINT "Message_receiverId_fkey" FOREIGN KEY ("receiverId") REFERENCES "User"("id") ON DELETE CASCADE ON UPDATE CASCADE,
	CONSTRAINT "Message_not_self" CHECK ("senderId" <> "receiverId")
);

CREATE TABLE IF NOT EXISTS "Notification" (
	"id" SERIAL PRIMARY KEY,
	"type" "NotificationType" NOT NULL,
	"userId" INTEGER NOT NULL,
	"fromUserId" INTEGER NOT NULL,
	"postId" INTEGER,
	"read" BOOLEAN NOT NULL DEFAULT false,
	"createdAt" TIMESTAMP(3) NOT NULL DEFAULT CURRENT_TIMESTAMP,
	CONSTRAINT "Notification_userId_fkey" FOREIGN KEY ("userId") REFERENCES "User"("id") ON DELETE CASCADE ON UPDATE CASCADE,
	CONSTRAINT "Notification_fromUserId_fkey" FOREIGN KEY ("fromUserId") REFERENCES "User"("id") ON DELETE CASCADE ON UPDATE CASCADE,
	CONSTRAINT "Notification_postId_fkey" FOREIGN KEY ("postId") REFERENCES "Post"("id") ON DELETE CASCADE ON UPDATE CASCADE
);

CREATE INDEX IF NOT EXISTS "User_email_idx" ON "User"("email");
CREATE INDEX IF NOT EXISTS "User_username_idx" ON "User"("username");
CREATE INDEX IF NOT EXISTS "Post_userId_idx" ON "Post"("userId");
CREATE INDEX IF NOT EXISTS "Post_createdAt_idx" ON "Post"("createdAt");
CREATE INDEX IF NOT EXISTS "Comment_postId_idx" ON "Comment"("postId");
CREATE INDEX IF NOT EXISTS "Comment_userId_idx" ON "Comment"("userId");
CREATE INDEX IF NOT EXISTS "Like_postId_idx" ON "Like"("postId");
CREATE INDEX IF NOT EXISTS "Friend_senderId_idx" ON "Friend"("senderId");
CREATE INDEX IF NOT EXISTS "Friend_receiverId_idx" ON "Friend"("receiverId");
CREATE INDEX IF NOT EXISTS "Friend_status_idx" ON "Friend"("status");
CREATE INDEX IF NOT EXISTS "Message_senderId_idx" ON "Message"("senderId");
CREATE INDEX IF NOT EXISTS "Message_receiverId_idx" ON "Message"("receiverId");
CREATE INDEX IF NOT EXISTS "Message_createdAt_idx" ON "Message"("createdAt");
CREATE INDEX IF NOT EXISTS "Notification_userId_idx" ON "Notification"("userId");
CREATE INDEX IF NOT EXISTS "Notification_userId_read_idx" ON "Notification"("userId", "read");
CREATE INDEX IF NOT EXISTS "Notification_createdAt_idx" ON "Notification"("createdAt");

CREATE OR REPLACE FUNCTION set_updated_at_timestamp()
RETURNS TRIGGER AS $$
BEGIN
	NEW."updatedAt" = CURRENT_TIMESTAMP;
	RETURN NEW;
END;
$$ LANGUAGE plpgsql;

DO $$
BEGIN
	IF NOT EXISTS (
		SELECT 1 FROM pg_trigger
		WHERE tgname = 'set_user_updated_at'
	) THEN
		CREATE TRIGGER set_user_updated_at
		BEFORE UPDATE ON "User"
		FOR EACH ROW
		EXECUTE FUNCTION set_updated_at_timestamp();
	END IF;
END $$;

DO $$
BEGIN
	IF NOT EXISTS (
		SELECT 1 FROM pg_trigger
		WHERE tgname = 'set_post_updated_at'
	) THEN
		CREATE TRIGGER set_post_updated_at
		BEFORE UPDATE ON "Post"
		FOR EACH ROW
		EXECUTE FUNCTION set_updated_at_timestamp();
	END IF;
END $$;

DO $$
BEGIN
	IF NOT EXISTS (
		SELECT 1 FROM pg_trigger
		WHERE tgname = 'set_comment_updated_at'
	) THEN
		CREATE TRIGGER set_comment_updated_at
		BEFORE UPDATE ON "Comment"
		FOR EACH ROW
		EXECUTE FUNCTION set_updated_at_timestamp();
	END IF;
END $$;

DO $$
BEGIN
	IF NOT EXISTS (
		SELECT 1 FROM pg_trigger
		WHERE tgname = 'set_friend_updated_at'
	) THEN
		CREATE TRIGGER set_friend_updated_at
		BEFORE UPDATE ON "Friend"
		FOR EACH ROW
		EXECUTE FUNCTION set_updated_at_timestamp();
	END IF;
END $$;
