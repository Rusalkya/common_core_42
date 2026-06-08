/**
 * @responsable clfouger
 * COMPOSANT CANVAS - Le cœur du systeme de dessin
 * 
 * Gere:
 * - Dessin a la souris ET tactile
 * - Undo/Redo
 * - Differents outils (pinceau, gomme, lignes, etc)
 */

import { useRef, useEffect, useState } from 'react'

export const Canvas = ({
  width = 800,
  height = 600,
  onImageUpdate,
  tool = 'brush',
  color = '#000000',
  size = 5,
  opacity = 1
}) => {
  const canvasRef = useRef(null)
  const [isDrawing, setIsDrawing] = useState(false)
  const [history, setHistory] = useState([])
  const [historyStep, setHistoryStep] = useState(-1)
  const contextRef = useRef(null)

  // Initialiser le canvas
  useEffect(() => {
    const canvas = canvasRef.current
    canvas.width = width
    canvas.height = height

    const context = canvas.getContext('2d')
    context.fillStyle = 'white'
    context.fillRect(0, 0, width, height)
    context.lineCap = 'round'
    context.lineJoin = 'round'
    contextRef.current = context

    // Sauvegarder l'etat initial
    saveHistory()
  }, [width, height])

  const saveHistory = () => {
    const canvas = canvasRef.current
    const newHistory = history.slice(0, historyStep + 1)
    newHistory.push(canvas.toDataURL())
    setHistory(newHistory)
    setHistoryStep(newHistory.length - 1)
    onImageUpdate?.(canvas.toDataURL('image/png'))
  }

  const startDrawing = (e) => {
    const { offsetX, offsetY } = getCoordinates(e)
    setIsDrawing(true)

    const context = contextRef.current
    context.globalAlpha = opacity
    context.strokeStyle = color
    context.lineWidth = size

    if (tool === 'eraser') {
      context.clearRect(offsetX - size / 2, offsetY - size / 2, size, size)
    } else {
      context.beginPath()
      context.moveTo(offsetX, offsetY)
    }
  }

  const draw = (e) => {
    if (!isDrawing) return

    const { offsetX, offsetY } = getCoordinates(e)
    const context = contextRef.current

    if (tool === 'eraser') {
      context.clearRect(offsetX - context.lineWidth / 2, offsetY - context.lineWidth / 2, context.lineWidth, context.lineWidth)
    } else if (tool === 'brush') {
      context.lineTo(offsetX, offsetY)
      context.stroke()
    } else if (tool === 'line') {
      // Les lignes se dessinent on release
    }
  }

  const stopDrawing = () => {
    if (!isDrawing) return

    setIsDrawing(false)
    contextRef.current.closePath()
    saveHistory()
  }

  const getCoordinates = (e) => {
    const canvas = canvasRef.current
    const rect = canvas.getBoundingClientRect()

    if (e.touches) {
      // Touch event
      return {
        offsetX: e.touches[0].clientX - rect.left,
        offsetY: e.touches[0].clientY - rect.top
      }
    }

    // Mouse event
    return {
      offsetX: e.clientX - rect.left,
      offsetY: e.clientY - rect.top
    }
  }

  const undo = () => {
    if (historyStep > 0) {
      const newStep = historyStep - 1
      setHistoryStep(newStep)
      loadFromHistory(newStep)
    }
  }

  const redo = () => {
    if (historyStep < history.length - 1) {
      const newStep = historyStep + 1
      setHistoryStep(newStep)
      loadFromHistory(newStep)
    }
  }

  const loadFromHistory = (step) => {
    const img = new Image()
    img.src = history[step]
    img.onload = () => {
      const context = contextRef.current
      context.clearRect(0, 0, width, height)
      context.drawImage(img, 0, 0)
      onImageUpdate?.(history[step])
    }
  }

  const clear = () => {
    const context = contextRef.current
    context.fillStyle = 'white'
    context.fillRect(0, 0, width, height)
    saveHistory()
  }

  const downloadImage = () => {
    const canvas = canvasRef.current
    const link = document.createElement('a')
    link.href = canvas.toDataURL('image/png')
    link.download = `dessin-${Date.now()}.png`
    link.click()
  }

  return {
    canvas: (
      <canvas
        ref={canvasRef}
        className="canvas"
        onMouseDown={startDrawing}
        onMouseMove={draw}
        onMouseUp={stopDrawing}
        onMouseLeave={stopDrawing}
        onTouchStart={startDrawing}
        onTouchMove={draw}
        onTouchEnd={stopDrawing}
        style={{
          cursor: tool === 'eraser' ? 'cell' : 'crosshair',
          borderRadius: 'var(--border-radius-md)'
        }}
      />
    ),
    undo,
    redo,
    clear,
    downloadImage,
    canUndo: historyStep > 0,
    canRedo: historyStep < history.length - 1,
    getImage: () => canvasRef.current.toDataURL('image/png')
  }
}
