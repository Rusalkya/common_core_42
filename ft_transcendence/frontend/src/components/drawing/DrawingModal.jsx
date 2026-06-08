/**
 * @responsable clfouger
 * COMPOSANT DRAWING MODAL - La pop-up de dessin (style Twitter)
 * 
 * - Dessin en grand avec canvas
 * - Barre d'outils
 * - Boutons de publication
 * - Support mobile responsif
 */

import { useState, useRef } from 'react'
import { Modal } from '../ui/Modal'
import { Button } from '../ui/Button'
import { Canvas } from './Canvas'
import { Toolbar } from './Toolbar'
import { useNotification } from '../../context/NotificationContext'
import { postService } from '../../services/postService'

export const DrawingModal = ({ isOpen, onClose, onPostCreated }) => {
  const { success, error } = useNotification()
  const canvasController = useRef(null)
  const [tool, setTool] = useState('brush')
  const [color, setColor] = useState('#000000')
  const [size, setSize] = useState(5)
  const [opacity, setOpacity] = useState(1)
  const [description, setDescription] = useState('')
  const [isLoading, setIsLoading] = useState(false)
  const [imageData, setImageData] = useState(null)

  const handlePublish = async () => {
    if (!imageData) {
      error('Veuillez dessiner quelque chose avant de publier')
      return
    }

    setIsLoading(true)
    try {
      // Convertir dataURL en blob
      const blob = await fetch(imageData).then(r => r.blob())
      
      await postService.create(blob, description)
      success('Dessin publie avec succes!')
      
      // Reinitialiser et fermer
      setDescription('')
      setImageData(null)
      onPostCreated?.()
      onClose()
    } catch (err) {
      error(`Erreur: ${err.message}`)
    } finally {
      setIsLoading(false)
    }
  }

  const handleCanvasMount = (controller) => {
    canvasController.current = controller
  }

  return (
    <Modal
      isOpen={isOpen}
      onClose={onClose}
      title="Creer un dessin"
      size="large"
      className="drawing-modal"
    >
      <div className="drawing-container">
        {/* Canvas et outils */}
        <div className="drawing-canvas-wrapper">
          <div className="drawing-canvas">
            {isOpen && (
              <CanvasWrapper 
                onMount={handleCanvasMount}
                tool={tool}
                color={color}
                size={size}
                opacity={opacity}
                onImageUpdate={setImageData}
              />
            )}
          </div>

          {/* Toolbar */}
          <Toolbar
            tool={tool}
            onToolChange={setTool}
            color={color}
            onColorChange={setColor}
            size={size}
            onSizeChange={setSize}
            opacity={opacity}
            onOpacityChange={setOpacity}
            onUndo={() => canvasController.current?.undo()}
            onRedo={() => canvasController.current?.redo()}
            onClear={() => canvasController.current?.clear()}
            canUndo={canvasController.current?.canUndo}
            canRedo={canvasController.current?.canRedo}
          />
        </div>

        {/* Sidebar actions */}
        <div className="drawing-sidebar">
          {/* Apercu */}
          {imageData && (
            <div className="drawing-preview">
              <img src={imageData} alt="Apercu" />
            </div>
          )}

          {/* Description */}
          <textarea
            placeholder="Ajoute une description (optionnel)..."
            value={description}
            onChange={(e) => setDescription(e.target.value)}
            className="input"
            style={{ resize: 'none', height: '100px' }}
          />

          {/* Boutons d'action */}
          <div className="drawing-actions">
            <Button
              variant="secondary"
              onClick={onClose}
              disabled={isLoading}
            >
              Annuler
            </Button>
            <Button
              variant="primary"
              onClick={handlePublish}
              disabled={isLoading || !imageData}
            >
              {isLoading ? 'Publication...' : 'Publier'}
            </Button>
          </div>
        </div>
      </div>
    </Modal>
  )
}

// Composant wrapper pour monter le Canvas
const CanvasWrapper = ({ onMount, tool, color, size, opacity, onImageUpdate }) => {
  const controller = Canvas({
    width: 800,
    height: 500,
    tool,
    color,
    size,
    opacity,
    onImageUpdate
  })

  useState(() => {
    onMount(controller)
  }, [])

  return controller.canvas
}
